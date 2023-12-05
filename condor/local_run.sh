#!/bin/bash

while read -r line
do
  echo "$line"
  echo "Running.."
  root -l 'fileSkimmer.C('\"$line\"')'
  echo ""
done < $1

#echo "Running..."

# Set up ATLAS on this machine:
#source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

#export myFile=$1

#ls

#root -l 'fileSkimmer.C('\"$myFile\"')'
