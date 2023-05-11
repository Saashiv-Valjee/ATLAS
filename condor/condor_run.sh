#!/bin/bash

echo "Running..."

# Set up ATLAS on this machine:
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

export myFile=$1

ls

root -l 'fileSkimmer.C('\"$myFile\"')'
