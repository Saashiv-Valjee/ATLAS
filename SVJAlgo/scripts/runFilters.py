#!/usr/bin/python

##################################################
# A tool to group files into periods
# It prints out blocks for each periods that
# can be directly copied to the sample 
# dictionaries in Samples.py
# It also checks local data integrity
# command:
#    python runFilters.py filelist year integrity  
# bingxuan.liu@cern.ch
#################################################

import os 
import sys

runDicMaster = {
  "2017" : {
    "A" : [324320, 325558],
    "B" : [325713, 328393],
    "C" : [329385, 330470],
    "D" : [330857, 332304],
    "E" : [332720, 334779],
    "F" : [334842, 335290],
    "H" : [336497, 336782],
    "I" : [336832, 337833],
    "K" : [338183, 340453],
    "N" : [341257, 341649],
  },
  "2018" : {
    "B" : [348885, 349533],
    "C" : [349534, 350220],
    "D" : [350310, 352107],
    "E" : [352123, 352137],
    "F" : [352274, 352514],
    "G" : [354107, 354494],
    "H" : [354826, 355224],
    "I" : [355261, 355273],
    "J" : [355331, 355468],
    "K" : [355529, 356259],
    "L" : [357050, 359171],
    "M" : [359191, 360414],
    "O" : [361738, 363400],
    "Q" : [363664, 364292],
  },
}

runListsMaster = {
  "2017" : {
    "A" : [],
    "B" : [],
    "C" : [],
    "D" : [],
    "E" : [],
    "F" : [],
    "H" : [],
    "I" : [],
    "K" : [],
    "N" : [],
  },
  "2018" : {
    "B" : [],
    "C" : [],
    "D" : [],
    "E" : [],
    "F" : [],
    "G" : [],
    "H" : [],
    "I" : [],
    "J" : [],
    "K" : [],
    "L" : [],
    "M" : [],
    "O" : [],
    "Q" : [],
  },
}  

inputDataList = open(str(sys.argv[1]),"r")
year = str(sys.argv[2])

runDic = runDicMaster[year]
runLists = runListsMaster[year]

for line in inputDataList:
  runNumber = int(line.split('.')[1])
  for runPeriod in runDic:
    if runNumber <= runDic[runPeriod][1] and runNumber >= runDic[runPeriod][0]:
      runLists[runPeriod].append(line.rstrip('\n'))
for runPeriod in runDic:
  print '"' + runPeriod + '_' + year + '" : ' 
  print runLists[runPeriod]

integrity = str(sys.argv[3])

if integrity == "y":
  
  localDataDir = "/atlasfs/atlas/local/bingxuan.liu/FourJetNtuple/2017Data/"
  
  periodToCheck = ["B", "C", "D", "E", "F", "H", "I"] 
  
  print "Checking data integrity in local disk: " + localDataDir + "\n"
  
  if os.path.exists("missingFiles.txt"):
    os.system("rm missingFiles.txt")
  os.system("touch missingFiles.txt")
  missingFile = open("missingFiles.txt","r+w")
  for period in periodToCheck:
    print "Checking data integrity in period " + period + ": "
    for run in runLists[period]:
      runNumber = int(run.split('.')[1]) 
      files = os.popen("ls " + localDataDir + period + "/" + "*" + str(runNumber) + "*").readlines()
      if not len(files):
        print "Run " + str(runNumber) + " is missing!!!!"
        print "The dataset is " + run + "!"   
        missingFile.write(run + "\n")
  
  runListLine = os.popen("grep 'RunList' ../data/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_JetHLT_Normal2017.xml").readlines()
  runLists = runListLine[0].split(">")[1].split("<")[0].split(",")
  for run in runLists:
    files = os.popen("ls " + localDataDir + "*/*" + str(run) + "*").readlines()
    if not len(files):
      print "Run " + str(run) + " is missing!!!"
      os.system("rucio ls data17_13TeV.00" + str(run) + ".physics_Main.deriv.DAOD_EXOT2.**")
