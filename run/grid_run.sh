loglevel=info

# this  has to be somewhere you can write
#parentsubmitdir="/afs/cern.ch/user/j/jodavies/darkjetresonances/DAODtoNTUPLE/run/"
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/newAH/ana-exot-2021-19/run/"
WorkDir_DIR="/afs/cern.ch/work/e/ebusch/public/SVJ/newAH/ana-exot-2021-19"
configFile=$WorkDir_DIR/configs/cutflow_signal_DAODtoNTUPLE_mc.py

submitdir=grid_multijet
inputFile=multijet_mc16a.txt

xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.mc16a --optGridNGBPerJob=4

