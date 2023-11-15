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

xAODAnaHelpers and the SVJAlgorithm are now ready to use

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
TODO

## ML Tool Analysis
TODO

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

