loglevel=info

# this  has to be somewhere you can write
#parentsubmitdir="/afs/cern.ch/user/j/jodavies/darkjetresonances/DAODtoNTUPLE/run/"
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/xAHAnalysis/run/"
WorkDir_DIR="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/xAHAnalysis"
configFile=$WorkDir_DIR/src/SVJAlgo/data/config_SVJAlgo_bkg.py
sigconfigFile=$WorkDir_DIR/src/SVJAlgo/data/config_SVJAlgo_signal.py

#for BKG in ttbar wplusjets zplusjets
#for BKG in multijet zplusjets
#do
#	submitdir=grid_${BKG}
#	for MC in mc20a mc20d mc20e
#	do
#		inputFile=${BKG}_${MC}.txt
#		echo $inputFile
#		echo "xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --extraOptions="--doFatJet" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v5a.${MC} --optGridNGBPerJob=2"
#		xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --extraOptions="--doFatJet" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v5a.${MC} --optGridNGBPerJob=2
#	done
#done

for SIG in gridtest
do
	submitdir=grid_${SIG}
	for MC in mc20e
	do
		inputFile=${SIG}_${MC}.txt
		echo $inputFile
		echo "xAH_run.py --inputRucio --inputList --files $inputFile --config $sigconfigFile --extraOptions="--doFatJet" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v5a.${MC} --optGridNGBPerJob=2"
		xAH_run.py --inputRucio --inputList --files $inputFile --config $sigconfigFile --extraOptions="--doFatJet" --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v6test1.${MC} --optGridNGBPerJob=2
	done
done


#submitdir=grid_multijet
#inputFile=multijet_mc16e.txt


#xAH_run.py --inputRucio --inputList --files $inputFile --config $configFile --force --submitDir $submitdir prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.ebusch.%in:name[2]%.%in:name[3]%.v3a.mc16e --optGridNGBPerJob=4

