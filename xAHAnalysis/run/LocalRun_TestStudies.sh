loglevel=info
extra=""
#extra="--inputList"

# this  has to be somewhere you can write
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/xAHAnalysis/run/"
infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v5/mc20_13TeV.515499.MGPy8EG_SVJSChan2j_2000_2.deriv.DAOD_PHYS.e8461_s3995_r13145_p5440/DAOD_PHYS.31296012._000001.pool.root.1"
configFile=../src/SVJAlgo/data/config_SVJAlgo_signal.py

nevents=10
submitdir=DAODtoTTREE_${nevents}


echo "xAH_run.py --files ${infile} --nevents $nevents --config $configFile --extraOptions="--doFatJet" --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct "
xAH_run.py --files ${infile} --nevents $nevents --config $configFile --extraOptions="--doFatJet" --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct 

# test command for using rucio with file list
#filelisttxt="/afs/cern.ch/user/m/mamerl/TLAWork/inputlisttest.txt"
#echo "xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct"
#xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct

#The large-R jets are not used by default. To turn it on you should do:

#xAH_run.py --config ../ana-exot-2021-19/SVJAlgo/data/config_SVJAlgo_ZJets.py --files /eos/user/b/biliu/mc20_13TeV/DAOD_PHYS.28690183._000001.pool.root.1 --extraOptions="--doFatJet" --isMC --submitDir test direct
