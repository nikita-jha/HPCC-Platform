#!/bin/bash
#
# Common utilities used by tools for automating tagging and release
#
set -e

VERSIONFILE=Chart.yaml
if [ ! -f $VERSIONFILE ]; then
  echo "Expected $VERSIONFILE not found"
  exit 2
fi


function parse_cmake()
{
  HPCC_PROJECT=$(grep -m1 '^name:' $VERSIONFILE | sed "s/^name: *//")
  HPCC_NAME="Helm Chart for $HPCC_PROJECT"
  HPCC_VERSION=$(grep -m1 '^version:' $VERSIONFILE | sed "s/^version: *//")

  HPCC_MAJOR=$(echo $HPCC_VERSION | awk 'BEGIN {FS="[.-]"}; {print $1};')
  HPCC_MINOR=$(echo $HPCC_VERSION | awk 'BEGIN {FS="[.-]"}; {print $2};')
  HPCC_POINT=$(echo $HPCC_VERSION | awk 'BEGIN {FS="[.-]"}; {print $3};')
  HPCC_MATURITY=$(echo $HPCC_VERSION | awk 'BEGIN {FS="[-.+]"}; {print $4};' | sed 's/[0-9]//g')
  HPCC_SEQUENCE=$(echo $HPCC_VERSION | awk 'BEGIN {FS="[-.+]"}; {print $4};' | sed 's/[^0-9]//g')

  # translate maturity/sequence to what go_rc/go_gold understand
  if [ -z "$HPCC_MATURITY" ] ; then
    HPCC_MATURITY=release
  fi
  # translate maturity to what go_rc/go_gold understand
  if [ -z "$HPCC_SEQUENCE" ] ; then
    HPCC_SEQUENCE=1
  fi

    echo "file $VERSIONFILE"
    echo "PROJECT $HPCC_PROJECT"
    echo "VERSION $HPCC_VERSION"
    echo "MAJOR $HPCC_MAJOR"
    echo "MINOR $HPCC_MINOR"
    echo "POINT $HPCC_POINT"
    echo "MATURITY $HPCC_MATURITY"
    echo "SEQ $HPCC_SEQUENCE"
  if ! `echo $HPCC_SEQUENCE | grep -Eq ^[0-9]+$`; then
    echo "Error: HPCC_SEQUENCE not an Integer"
    echo "-- possibly on branch using old versioning scheme"
    exit 2
  fi


}

function update_version_file()
{
    # Update the Chart.yaml file
    local _new_maturity=$1
    local _new_point=$2
    local _new_sequence=$3
    local _new_minor=$4
    if [ -z "$_new_minor" ] ; then
      _new_minor=$HPCC_MINOR
    fi
    if [ "$_new_maturity" == "release" ] ; then
      local _v=${HPCC_MAJOR}.${_new_minor}.${_new_point}
    else
      local _v=${HPCC_MAJOR}.${_new_minor}.${_new_point}-${_new_maturity}${_new_sequence}
    fi
    
    if [ -n "$VERBOSE" ] ; then
      echo sed -E \
       -e "s/^version: .*$/version: $_v/" \
       -e "s/^appVersion: .*$/appVersion: $_v/" \
       -i.bak $VERSIONFILE
    fi
    if [ -z "$DRYRUN" ] ; then 
      sed -E \
       -e "s/^version: .*$/version: $_v/" \
       -e "s/^appVersion: .*$/appVersion: $_v/" \
       -i.bak $VERSIONFILE
       cat $VERSIONFILE
    else
      sed -E \
       -e "s/^version: .*$/version: $_v/" \
       -e "s/^appVersion: .*$/appVersion: $_v/" \
       $VERSIONFILE
    fi
}
