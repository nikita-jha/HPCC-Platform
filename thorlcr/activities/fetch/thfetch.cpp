/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2012 HPCC Systems®.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
############################################################################## */

#include "platform.h"
#include "eclhelper.hpp"
#include "thbufdef.hpp"
#include "mptag.hpp"
#include "dadfs.hpp"
#include "jstats.h"
#include "thexception.hpp"

#include "../hashdistrib/thhashdistrib.ipp"
#include "thfetch.ipp"

class CFetchActivityMaster : public CMasterActivity
{
    Owned<CSlavePartMapping> mapping;
    MemoryBuffer offsetMapMb;
    SocketEndpoint *endpoints;
    std::vector<OwnedPtr<CThorStatsCollection>> subFileStats;

protected:
    IHThorFetchArg *helper;

public:
    CFetchActivityMaster(CMasterGraphElement *info) : CMasterActivity(info, diskReadActivityStatistics)
    {
        endpoints = NULL;
        if (!container.queryLocalOrGrouped())
            mpTag = container.queryJob().allocateMPTag();
        helper = (IHThorFetchArg *)queryHelper();
        reInit = 0 != (helper->getFetchFlags() & (FFvarfilename|FFdynamicfilename));
    }
    ~CFetchActivityMaster()
    {
        if (endpoints) free(endpoints);
    }
    virtual void init()
    {
        CMasterActivity::init();
        OwnedRoxieString fname(helper->getFileName());
        Owned<IDistributedFile> fetchFile = queryThorFileManager().lookup(container.queryJob(), fname, false, 0 != (helper->getFetchFlags() & FFdatafileoptional), false, container.activityIsCodeSigned());
        if (fetchFile)
        {
            if (isFileKey(fetchFile))
                throw MakeActivityException(this, TE_FileTypeMismatch, "Attempting to read index as a flat file: %s", fname.get());
            Owned<IFileDescriptor> fileDesc = getConfiguredFileDescriptor(*fetchFile);
            void *ekey;
            size32_t ekeylen;
            helper->getFileEncryptKey(ekeylen,ekey);
            bool encrypted = fileDesc->queryProperties().getPropBool("@encrypted");
            if (0 != ekeylen)
            {
                memset(ekey,0,ekeylen);
                free(ekey);
                if (!encrypted)
                {
                    Owned<IException> e = MakeActivityWarning(&container, TE_EncryptionMismatch, "Ignoring encryption key provided as file '%s' was not published as encrypted", fetchFile->queryLogicalName());
                    queryJobChannel().fireException(e);
                }
            }
            else if (encrypted)
                throw MakeActivityException(this, 0, "File '%s' was published as encrypted but no encryption key provided", fetchFile->queryLogicalName());
            IDistributedSuperFile *super = fetchFile->querySuperFile();
            unsigned numsubs = super?super->numSubFiles(true):0;
            for (unsigned i=0; i<numsubs; i++)
                subFileStats.push_back(new CThorStatsCollection(diskReadActivityStatistics));

            mapping.setown(getFileSlaveMaps(fetchFile->queryLogicalName(), *fileDesc, container.queryJob().queryUserDescriptor(), container.queryJob().querySlaveGroup(), container.queryLocalOrGrouped(), false, NULL, super));
            mapping->serializeFileOffsetMap(offsetMapMb);
            addReadFile(fetchFile);
        }
    }
    virtual void serializeSlaveData(MemoryBuffer &dst, unsigned slave)
    {
        if (mapping)
        {
            mapping->serializeMap(slave, dst);
            dst.append(offsetMapMb);
        }
        else
        {
            CSlavePartMapping::serializeNullMap(dst);
            CSlavePartMapping::serializeNullOffsetMap(dst);
        }
        if (!container.queryLocalOrGrouped())
            dst.append((int)mpTag);
    }
    virtual void deserializeStats(unsigned node, MemoryBuffer &mb) override
    {
        CMasterActivity::deserializeStats(node, mb);
        for (auto &stats: subFileStats)
            stats->deserialize(node, mb);
    }
    virtual void done() override
    {
        if (!subFileStats.empty())
        {
            unsigned numSubFiles = subFileStats.size();
            for (unsigned i=0; i<numSubFiles; i++)
            {
                IDistributedFile *file = queryReadFile(i);
                if (file)
                    file->addAttrValue("@numDiskReads", subFileStats[i]->getStatisticSum(StNumDiskReads));
            }
        }
        else
        {
            IDistributedFile *file = queryReadFile(0);
            if (file)
                file->addAttrValue("@numDiskReads", statsCollection.getStatisticSum(StNumDiskReads));
        }
        CMasterActivity::done();
    }
};

class CCsvFetchActivityMaster : public CFetchActivityMaster
{
public:
    CCsvFetchActivityMaster(CMasterGraphElement *info) : CFetchActivityMaster(info) { }
    virtual void serializeSlaveData(MemoryBuffer &dst, unsigned slave)
    {
        CFetchActivityMaster::serializeSlaveData(dst, slave);
        IDistributedFile *fetchFile = queryReadFile(0);
        if (fetchFile)
            fetchFile->queryAttributes().serialize(dst);
    }
};

class CXmlFetchActivityMaster : public CFetchActivityMaster
{
public:
    CXmlFetchActivityMaster(CMasterGraphElement *info) : CFetchActivityMaster(info)
    {
    }
};


CActivityBase *createFetchActivityMaster(CMasterGraphElement *container)
{
    return new CFetchActivityMaster(container);
}

CActivityBase *createCsvFetchActivityMaster(CMasterGraphElement *container)
{
    return new CCsvFetchActivityMaster(container);
}

CActivityBase *createXmlFetchActivityMaster(CMasterGraphElement *container)
{
    return new CXmlFetchActivityMaster(container);
}

