# SVJ s-channel Analysis - xAODAnaHelpers

Codes for nTuple creation and evaluation using xAODAnaHelpers, with specialized package extensions for truth information

## Installation

Below is a step-by-step guide for install the SVJAlgo xAODAnaHelpers framework. If there are any questions about this guide, please contact Bing or Elena at: bingxuan.liu@cern.ch and ebusch@cern.ch 

1. git clone https://gitlab.cern.ch/atlas-phys/exot/jdm/ana-exot-2021-19.git
2. cd ana-exot-2021-19
3. git submodule status - see that xAHAnalysis/src/xAODAnaHelpers is listed as a submodule
4. git submodule update --init
5. cd xAHAnalysis
6. setupATLAS (if not yet done in bashrc)
7. source install.sh
8. mkdir run

### Local Athena Release Build - R24
In order to implement the JetTileCorrectionTool fix, you will need to setup a local version of athena.
1. Inside xAHAnalysis, do the follwing
  1. git clone https://:@gitlab.cern.ch:8443/atlas/athena.git
  2. cd athena
  3. git checkout release/24.2.25
2. Navigate back to the xAHAnalysis area, then to the src/xAODAnaHelpers area
  1. Check commit 0111e8c (for R24.2.30)
3. Copy src/xAODAnaHelpers and src/SVJAlgo to localRelease/athena/Projects/WorkDir
  1. Note this means that if you modify something in SVJAlgo, you should first modify it in src/SVJAlgo so that the changes are stored to this git, and then copy the folder again to the localRelease area. TODO: symlink instead so we don't have this issue??
4. Copy the files in tileFiles to the folliwng places:
  1. `cp tileFiles/Tile_maskedDB_Run2_fromChristos.conf localRelease/athena/Reconstruction/Jet/JetAnalysisTools/JetTileCorrection/data/` 
  2. `cp tileFiles/JetTileCorrectionTool.cxx localRelease/athena/Reconstruction/Jet/JetAnalysisTools/JetTileCorrection/Root/`
  3. `cp tileFiles/JetTileCorrectionTool.h localRelease/athena/Reconstruction/Jet/JetAnalysisTools/JetTileCorrection/JetTileCorrection/`
  4. `cp tileFiles/IJetTileCorrectionTool.h localRelease/athena/Reconstruction/Jet/JetCPInterfaces/JetCPInterfaces/`
5. In the xAHAnalysis area, run `source setup.sh`. Make sure the correct release (24.2.25) is set up
6. Compile using `source compile.sh`. Note if you are replacing an existing build, you should delete and recreate the build direcotry to ensure the new release information is picked up properly.

xAODAnaHelpers and the SVJAlgorithm are now ready to use. The key changes from the tileFiles version are adding the updated masked tile config file, and enabling checking of LB information.

## Running xAODAnaHelpers Locally

1. cd xAHAnalysis
2. source setup.sh - take note of AnalysisBase release
3. cd run
4. Run the xAH\_run.py command with the following form:
```
xAH_run.py --config ../src/SVJAlgo/data/config_SVJAlgo_QCD.py --files  /eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v4/test_multijet/DAOD_PHYS.30165462._000062.pool.root.1  --isMC --submitDir test direct
``` 

## Grid Running with xAODAnaHelpers
1. source setup.sh
2. lsetup panda
3. cd run
4. source grid\_run.sh

**Note**: Jobs can be monitored via the `pbook` feature of panda, or the BigPandaMon website `https://bigpanda.cern.ch/user/`. `Finished` jobs can be retried to get to 100% `done` via the folliwng:
1. lsetup panda
2. pbook
3. show()
4. retry([JediTaskID1,JediTaskID2,JediTaskID3,...])


## Making MicroNTuples

The MicroNTupleMaker code provides a framework for applying essential analysis cuts and calculating analysis variables of interest, which can then be saved in a tree/nTuple format for easy access without the need to recalculate every time. 

### Installing MicroNTuple code
First, create a directory called MicroNTuples where your output will live, and a directory for the executable.
```
cd MicroNTupleMaker
mkdir MicroNTuples
mkdir exe
```
### Compiling MicroNtuple code
In the MicroNTupleMaker directory, you can compile the code with the compilation script (g++).

**Note**: There appear to be conflicts with this code, and the AnalysisBase release needed for AnalysisTop. I will try to resolve this in the future, but for now you should log out, start with a clean terminal, and then setup the needed root version using the setup script.
```
cd MicroNTupleMaker
source setup.sh
source compile.sh
```

The executable takes 1 or 3 arguemnts; the file tag (`<file_tag>/some_files*.root`), and optionally a flag indicating whether you are running locally and a path to the input NTuples. By default the input NTuples are assumed to be in the run folder. Usage examples are shown below.
```
./exe/MicroNTupleMaker file_tag
./exe/MicroNTupleMaker file_tag true /my/unique/input/path/
```

### Running MicroNTuple code on the grid
As of nTuple v2, all xAH nTuples live on the grid and are not intended to be downloaded locally. As such, once your changed to the microNtuple code have been tested locally, you should run the code over the nTuples on the grid. This can be done with the following sequence (in a clean terminal):
```
setupATLAS
lsetup panda
./grid_run.sh

```
Note that `grid_run.sh` executes a prun command, which depends on the maps `filemap_multijet.json` or `filemap_signal.json`. These files should be editted before running to give the correct input nTuple version, and the desired output name.

## Weight calculation
### Setup
1. Use rucio to download samples to the eos space
2. Hadd individual input files into mc groups using the script `hadd_input`. Edit the scrip to the correct version number first. This is important to have the correct totalWeight for each DSID+mcCampaign in the metaData histogram, which is used in the weight calculation.
3. Navigate to the condor/ area. Open the script `make_file_lists.sh`. Edit the eosPath variable to point to the new files, and make sure the user handle, in both the eosPath and the find commands, is correct for your files. Edit the name of the text files that are created to reflect your version number.
4. Source `make_file_lists`. This creates two lists; one containing files less than 900 MB, which will be processed on condor (max output file transfer size for condor is 1GB). The 2nd should contain just a few files which are larger than 900MB; for now the best option is to process these files locally. Instructions for both are provided.

### Condor processing
1. In the condor/ area, make a new directory corresponding to the version number, ie "`mkdir v9.1`. This will be your working directory
2. In submitCondor.py, edit line 6 to point to the eos area where you downloaded the files. Edit the for loop in line 13 to the name of the text file containing the small condor files for processing (eg `[vXX_files.txt]`. Edit line 43 `initialdir =` to the new initial directory you created in the previous step.
3. Ensure all the filepaths in the submitCondor.py file make sense for your work area (hardcoded to ebusch)
4. `python submitCondor.py` when you are ready to run
TODO: file to check output quality

### Local processing
1. copy the following files to the eos location with your files:
```
cp fileSkimmer.C fileSkimmer.h local_run.s vXX_large_files.txt /my/eos/path/
```
2. Navigate to the eos area where you just copied these files. The fileSkimmer codes parses the input file path, so it works better when executed in the same directory as the target files.
3. run `source local_run.sh vXX_large_files.txt` in the eos area. In general this will take 5-10 minutes. Your files with the weight calculation will appear in the eos area.

## ML Tool Analysis
TODO - document
TODO - # of events checker, loopers

## Plotting

Scripts are available in the Results folder to facilitate plotting from the MicroNtuples.

`MicroNTuplePlotterClass.h`: a class with many tool for creating stacks of histograms, applying weights and cuts, and plotting in ATLAS format  
`myPlotter.C`: set options and call plotter class instance to create plots  
`PlotFunctions.h`: some functions called by the plotter class  
`PlotParams.h`: Set plotting parameters (title, nBins, xmin, xmax) for each MicroNtuple branch  
`plotterExamples.C`: along with `myPlotter.C`, look here for examples of plotter class functionality  
`simplePlotter.C`: a separate standalone script ideal for making quick, specific modifications to 1D histogram plots

### EventDisplays

Joel's event display code. See internal README.

