loglevel=info

# this  has to be somewhere you can write
#parentsubmitdir="/afs/cern.ch/user/j/jodavies/darkjetresonances/DAODtoNTUPLE/run/"
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/newAH/ana-exot-2021-19/run/"
WorkDir_DIR="/afs/cern.ch/work/e/ebusch/public/SVJ/newAH/ana-exot-2021-19"
configFile=$WorkDir_DIR/configs/cutflow_signal_DAODtoNTUPLE_mc.py

submitdir=grid_signals_test
inputFile=svj_signals_mc16e.txt

#xAH_run.py --files ${infile} --config $configFile --isMC --submitDir ${parentsubmitdir}/$submitdir direct 

xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.mc16e --optGridNGBPerJob=4

# test command for using rucio with file list
#filelisttxt="/afs/cern.ch/user/m/mamerl/TLAWork/inputlisttest.txt"
#echo "xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct"
#xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct
