/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2016 HPCC Systems®.

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

#ifndef _ECLWATCH_ERRORLIST_HPP__
#define _ECLWATCH_ERRORLIST_HPP__

#include "errorlist.h"
#include "jlog.hpp"

#define ERRORMSG_INTERNAL       "An internal system error occured. The error information has been saved into a system log file."

#define ECLWATCH_INTERNAL_ERROR                 ECLWATCH_ERROR_START
#define ECLWATCH_ADMIN_ACCESS_DENIED            ECLWATCH_ERROR_START+1
#define ECLWATCH_SUPER_USER_ACCESS_DENIED       ECLWATCH_ERROR_START+2
#define ECLWATCH_SMC_ACCESS_DENIED              ECLWATCH_ERROR_START+3
#define ECLWATCH_THOR_QUEUE_ACCESS_DENIED       ECLWATCH_ERROR_START+4
#define ECLWATCH_EXECUTION_ACCESS_DENIED        ECLWATCH_ERROR_START+5
#define ECLWATCH_MACHINE_INFO_ACCESS_DENIED ECLWATCH_ERROR_START+6
#define ECLWATCH_METRICS_ACCESS_DENIED          ECLWATCH_ERROR_START+7
#define ECLWATCH_TOPOLOGY_ACCESS_DENIED     ECLWATCH_ERROR_START+8
#define ECLWATCH_ROXIE_QUERY_ACCESS_DENIED  ECLWATCH_ERROR_START+9
#define ECLWATCH_ECL_WU_ACCESS_DENIED           ECLWATCH_ERROR_START+10
#define ECLWATCH_DFU_ACCESS_DENIED              ECLWATCH_ERROR_START+11
#define ECLWATCH_DFU_XREF_ACCESS_DENIED     ECLWATCH_ERROR_START+12
#define ECLWATCH_DFU_WU_ACCESS_DENIED           ECLWATCH_ERROR_START+13
#define ECLWATCH_DFU_EX_ACCESS_DENIED           ECLWATCH_ERROR_START+14
#define ECLWATCH_FILE_SPRAY_ACCESS_DENIED       ECLWATCH_ERROR_START+15
#define ECLWATCH_FILE_DESPRAY_ACCESS_DENIED ECLWATCH_ERROR_START+16

#define ECLWATCH_INVALID_SEC_MANAGER            ECLWATCH_ERROR_START+30
#define ECLWATCH_INVALID_ACCOUNT_NAME           ECLWATCH_ERROR_START+31
#define ECLWATCH_INVALID_RESOURCE_NAME          ECLWATCH_ERROR_START+32
#define ECLWATCH_INVALID_PERMISSION_NAME        ECLWATCH_ERROR_START+33
#define ECLWATCH_CANNOT_CHANGE_PASSWORD     ECLWATCH_ERROR_START+34

#define ECLWATCH_INVALID_FILE_FOLDER            ECLWATCH_ERROR_START+35
#define ECLWATCH_INVALID_FILE_TYPE              ECLWATCH_ERROR_START+36
#define ECLWATCH_INVALID_FILE_NAME              ECLWATCH_ERROR_START+37
#define ECLWATCH_FILE_NOT_EXIST                 ECLWATCH_ERROR_START+38
#define ECLWATCH_CANNOT_OPEN_FILE               ECLWATCH_ERROR_START+39
#define ECLWATCH_CANNOT_READ_FILE               ECLWATCH_ERROR_START+40
#define ECLWATCH_NOT_SUPERFILE                  ECLWATCH_ERROR_START+41
#define ECLWATCH_FILE_ALREADY_EXISTS            ECLWATCH_ERROR_START+42

#define ECLWATCH_OLD_CLIENT_VERSION             ECLWATCH_ERROR_START+43
#define ECLWATCH_CANNOT_CONNECT_DALI            ECLWATCH_ERROR_START+44
#define ECLWATCH_CANNOT_GET_ENV_INFO            ECLWATCH_ERROR_START+45
#define ECLWATCH_CLUSTER_NOT_IN_ENV_INFO        ECLWATCH_ERROR_START+46
#define ECLWATCH_COMPONENT_NOT_IN_ENV_INFO  ECLWATCH_ERROR_START+47
#define ECLWATCH_INVALID_CLUSTER_INFO           ECLWATCH_ERROR_START+48
#define ECLWATCH_INVALID_CLUSTER_NAME           ECLWATCH_ERROR_START+49
#define ECLWATCH_CANNOT_RESOLVE_CLUSTER_NAME    ECLWATCH_ERROR_START+50

#define ECLWATCH_MISSING_PARAMS                 ECLWATCH_ERROR_START+51
#define ECLWATCH_INVALID_INPUT                  ECLWATCH_ERROR_START+52
#define ECLWATCH_INVALID_IP_OR_COMPONENT        ECLWATCH_ERROR_START+53
#define ECLWATCH_INVALID_COMPONENT_TYPE     ECLWATCH_ERROR_START+54
#define ECLWATCH_INVALID_COMPONENT_INFO     ECLWATCH_ERROR_START+55
#define ECLWATCH_INVALID_COMPONENT_OR_FILE_TYPE ECLWATCH_ERROR_START+56
#define ECLWATCH_INVALID_IP                     ECLWATCH_ERROR_START+57
#define ECLWATCH_INVALID_IP_RANGE               ECLWATCH_ERROR_START+58
#define ECLWATCH_INVALID_PROCESS_FILTER     ECLWATCH_ERROR_START+59

#define ECLWATCH_INVALID_ACTION                 ECLWATCH_ERROR_START+60
#define ECLWATCH_CANNOT_GET_FILE_ITERATOR       ECLWATCH_ERROR_START+61
#define ECLWATCH_GRAPH_NOT_FOUND                    ECLWATCH_ERROR_START+62
#define ECLWATCH_TOO_MANY_DATA_ROWS             ECLWATCH_ERROR_START+63
#define ECLWATCH_TOO_BIG_DATA_SET               ECLWATCH_ERROR_START+64
#define ECLWATCH_CANNOT_FIND_IXREFFILESNODE  ECLWATCH_ERROR_START+65
#define ECLWATCH_CANNOT_PARSE_ECL_QUERY     ECLWATCH_ERROR_START+66
#define ECLWATCH_CANNOT_COMPRESS_DATA           ECLWATCH_ERROR_START+67
#define ECLWATCH_CANNOT_CONNECT_ARCHIVE_SERVER  ECLWATCH_ERROR_START+68
#define ECLWATCH_ARCHIVE_SERVER_NOT_FOUND       ECLWATCH_ERROR_START+69
#define ECLWATCH_DROP_ZONE_NOT_FOUND            ECLWATCH_ERROR_START+70
#define ECLWATCH_INODE_NOT_FOUND                    ECLWATCH_ERROR_START+71
#define ECLWATCH_PROGRESS_INFO_NOT_FOUND        ECLWATCH_ERROR_START+72
#define ECLWATCH_ACCESS_TO_FILE_DENIED          ECLWATCH_ERROR_START+73
#define ECLWATCH_INVALID_DIRECTORY              ECLWATCH_ERROR_START+74

#define ECLWATCH_CANNOT_ACCESS_EXCEPTION_ENGINE ECLWATCH_ERROR_START+75
#define ECLWATCH_CANNOT_ACCESS_WU_ENGINE        ECLWATCH_ERROR_START+76
#define ECLWATCH_SINGLE_COLON_NOT_ALLOWED       ECLWATCH_ERROR_START+77
#define ECLWATCH_ID_MUST_BE_ALL_DIGITS          ECLWATCH_ERROR_START+78
#define ECLWATCH_CANNOT_CREATE_WORKUNIT     ECLWATCH_ERROR_START+79
#define ECLWATCH_CANNOT_GET_WORKUNIT            ECLWATCH_ERROR_START+80
#define ECLWATCH_CANNOT_OPEN_WORKUNIT           ECLWATCH_ERROR_START+81
#define ECLWATCH_CANNOT_UPDATE_WORKUNIT     ECLWATCH_ERROR_START+82
#define ECLWATCH_CANNOT_SUBMIT_WORKUNIT     ECLWATCH_ERROR_START+83
#define ECLWATCH_CANNOT_SCHEDULE_WORKUNIT       ECLWATCH_ERROR_START+84
#define ECLWATCH_CANNOT_DELETE_WORKUNIT     ECLWATCH_ERROR_START+85
#define ECLWATCH_QUERY_NOT_FOUND_FOR_WU     ECLWATCH_ERROR_START+86
#define ECLWATCH_CANNOT_CREATE_WUACTIONRESULT ECLWATCH_ERROR_START+87
#define ECLWATCH_CANNOT_GET_WU_RESULT           ECLWATCH_ERROR_START+88
#define ECLWATCH_CANNOT_CREATE_ARCHIVE_CMD  ECLWATCH_ERROR_START+89
#define ECLWATCH_ECLAGENT_LOG_NOT_FOUND     ECLWATCH_ERROR_START+90
#define ECLWATCH_MISSING_BANNER_CONTENT     ECLWATCH_ERROR_START+91
#define ECLWATCH_MISSING_CHAT_URL               ECLWATCH_ERROR_START+92
#define ECLWATCH_PLINK_NOT_INSTALLED            ECLWATCH_ERROR_START+93
#define ECLWATCH_PSEXEC_NOT_INSTALLED           ECLWATCH_ERROR_START+94
#define ECLWATCH_NO_WUID_SPECIFIED          ECLWATCH_ERROR_START+95

#define ECLWATCH_QUERYSET_NOT_FOUND         ECLWATCH_ERROR_START+96
#define ECLWATCH_QUERYID_NOT_FOUND          ECLWATCH_ERROR_START+97
#define ECLWATCH_ALIAS_NOT_FOUND            ECLWATCH_ERROR_START+98
#define ECLWATCH_QUERYSET_NOT_ON_CLUSTER    ECLWATCH_ERROR_START+99
#define ECLWATCH_CONTROL_QUERY_FAILED       ECLWATCH_ERROR_START+100
#define ECLWATCH_QUERY_SUSPENDED            ECLWATCH_ERROR_START+101
#define ECLWATCH_PACKAGEMAP_NOTRESOLVED     ECLWATCH_ERROR_START+102
#define ECLWATCH_RESOURCE_NOT_FOUND         ECLWATCH_ERROR_START+103
#define ECLWATCH_CANNOT_GET_STATUS_INFO     ECLWATCH_ERROR_START+104

#define ECLWATCH_VIEW_ACCESS_DENIED         ECLWATCH_ERROR_START+105
#define ECLWATCH_CANNOT_COPY_DLL            ECLWATCH_ERROR_START+106
#define ECLWATCH_INVALID_ECLRECDEF          ECLWATCH_ERROR_START+107


#endif //_ECLWATCH_ERRORLIST_HPP__

