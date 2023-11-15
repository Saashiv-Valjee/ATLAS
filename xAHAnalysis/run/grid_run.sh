loglevel=info

# this  has to be somewhere you can write
#parentsubmitdir="/afs/cern.ch/user/j/jodavies/darkjetresonances/DAODtoNTUPLE/run/"
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/xAHAnalysis/run/"
WorkDir_DIR="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/xAHAnalysis"
configFile=$WorkDir_DIR/src/SVJAlgo/data/config_SVJAlgo_MC.py
dataconfigFile=$WorkDir_DIR/src/SVJAlgo/data/config_SVJAlgo_data.py
#dataconfigFile=$WorkDir_DIR/localRelease/athena/Projects/WorkDir/SVJAlgo/data/config_SVJAlgo_data.py
#for data in data_all
#do
#	submitdir=grid_${data}
#	inputFile=${data}.txt
#	echo $inputFile
#	echo "xAH_run.py --inputRucio --inputList --files $inputFile --config $dataconfigFile --extraOptions="" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[1]%.%in:name[2]%.v10d --optGridNGBPerJob=2"
#	xAH_run.py --inputRucio --inputList --files $inputFile --config $dataconfigFile --extraOptions="" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[1]%.%in:name[2]%.v10d --optGridNGBPerJob=2
#done


#for BKG in wplusjets zplusjets #ttbar
for BKG in multijet #wplusjets ttbar
do
	submitdir=grid_${BKG}
	for MC in mc20a mc20d mc20e
	do
		inputFile=${BKG}_${MC}.txt
		echo $inputFile
		echo "xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --extraOptions="" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v11c.${MC} --optGridNGBPerJob=2"
		xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --extraOptions="" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v11c.${MC} --optGridNGBPerJob=2
	done
done

#for SIG in signal
#do
#	submitdir=grid_${SIG}
#	for MC in mc20a mc20d mc20e
#	do
#		inputFile=${SIG}_${MC}.txt
#		echo $inputFile
#		echo "xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --extraOptions="" --force --submitDir $submitdir prun $PUfile --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v11c.${MC} --optGridNGBPerJob=2"
#		xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --extraOptions="" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v11c.${MC} --optGridNGBPerJob=2
#	done
#done

