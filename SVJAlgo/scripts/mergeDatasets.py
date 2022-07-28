#!/usr/bin/python
##############################################
# This is a script to merge the outputs      #
# The idea is to merge smaller files into a  #
# bigger file with a threshold of 4GB        #
# to maximize the batch processing efficiency#
# You need to have your own version          #
##############################################

from ROOT import *
import optparse
import sys
import os
import re
import copy

runDirectoryStrings = os.popen("ls -d user.biliu*").readlines()
runDirectories = []

for string in runDirectoryStrings:
  if os.path.isdir(string.rstrip("\n")):
    runDirectories.append(string.rstrip("\n"))

def groupAndDelete(fileList, runNumber):
  newFileList = {}
  newFileList[fileList.keys()[0] + 1] = copy.deepcopy(fileList[fileList.keys()[0]])
  filesToMerge = []
  accumulatedSize = 0
  files = fileList[fileList.keys()[0]]
  for fileName in files:
    accumulatedSize = os.path.getsize(fileName) + accumulatedSize
    newFileList[fileList.keys()[0] + 1].remove(fileName)
    filesToMerge.append(fileName)
    if accumulatedSize > 4E9:
      break
  mergedFileName = ""
  if len(filesToMerge) == len(fileList[fileList.keys()[0]]) and fileList.keys()[0] == 1:
    mergedFileName = "user.biliu.PeriodB.Run" + str(runNumber) + ".physics_Main.Nominal.root"
  else:
    mergedFileName = "user.biliu.PeriodB.Run" + str(runNumber) + ".physics_Main.Nominal.Part" + str(fileList.keys()[0])  + ".root"
  mergeCommand = "hadd " + mergedFileName + " "
  deleteCommand = "rm "
  for fileEntry in filesToMerge:
    mergeCommand = mergeCommand + fileEntry + " "
    deleteCommand = deleteCommand + fileEntry + " "
  print mergeCommand
  os.system(mergeCommand)
  print deleteCommand
  os.system(deleteCommand)
  return  newFileList

for directory in runDirectories:
  runNumber = int(directory.split('.')[4])
  print "Now dealing with Run " + str(runNumber) + ":"
  os.chdir(directory)
  fileList = os.popen("ls *.root").readlines()
  fileNames = {1 : []}
  for fileName in fileList:
    fileNames[1].append(fileName.rstrip("\n"))
  while len(fileNames[fileNames.keys()[0]]):
    fileNames = groupAndDelete(fileNames,runNumber)
  os.chdir("/atlasfs/atlas/local/bingxuan.liu/FourJetNtuple/2017Data/B/")
