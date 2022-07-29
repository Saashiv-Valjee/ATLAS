Build:
===========================================
mkdir analysis
cd analysis
git clone --recursive https://:@gitlab.cern.ch:8443/biliu/ana-exot-2021-19.git
mkdir build
cd ana-exot-2021-19
asetup AnalysisBase,22.2.75,here
cd ../build
cmake ../ana-exot-2021-19
make
source x86*/setup.sh\cd ..

===========================================
It should be complied by now...you might see a bunch of warnings from xAODAnaHelpers

Run:
===========================================
cd ..
mkdir run
cd run

xAH_run.py --config ../ana-exot-2021-19/SVJAlgo/data/config_SVJAlgo_ZJets.py --files /eos/user/b/biliu/mc20_13TeV/DAOD_PHYS.28690183._000001.pool.root.1  --isMC --submitDir test direct

The "files" argument should be given a path to the input file (rel22 DAOD_PHYS). The test sample in biliu's local area is from a zjets sample: mc20_13TeV.700335.Sh_2211_Znunu_pTV2_BFilter.deriv.DAOD_PHYS.e8351_s3681_r13145_r13146_p5057
After it finishes, you should see a test ditectory that contains the output. The ntuple is located at test/data-tree/

The large-R jets are not used by default. To turn it on you should do:

xAH_run.py --config ../ana-exot-2021-19/SVJAlgo/data/config_SVJAlgo_ZJets.py --files /eos/user/b/biliu/mc20_13TeV/DAOD_PHYS.28690183._000001.pool.root.1 --extraOptions="--doFatJet" --isMC --submitDir test direct

Run on the grid:
xAH_run.py --inputRucio --inputList --files zjets.txt --config $WorkDir_DIR/data/SVJAlgo/config_SVJAlgo_ZJets.py --force --submitDir gridSubmission/test prun --optBatchShellInit 'source $WorkDir_DIR/setup.sh' --optGridOutputSampleName=user.biliu.dijet.%in:name[1]%.%in:name[2]%.%in:name[3]%.Nominal --optGridNGBPerJob=4

zjets.txt contains a list of sample names (for instance, mc20_13TeV.700335.Sh_2211_Znunu_pTV2_BFilter.deriv.DAOD_PHYS.e8351_s3681_r13145_r13146_p5057, etc), with one dataset per line. You need to change the output name to use your username in --optGridOutputSampleName
