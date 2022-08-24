# SVJ s-channel Analysis - xAODAnaHelpers

Codes for nTuple creation and evaluation using xAODAnaHelpers, with specialized package extensions for truth information

## Installation

Below is a step-by-step guide for install the SVJAlgo xAODAnaHelpers framework. If there are any questions about this guide, please contact Bing or Elena at: bingxuan.liu@cern.ch and ebusch@cern.ch 

TODO: test and finish

## Running xAODAnaHelpers Locally

TODO: test and finish

## Grid Running with xAODAnaHelpers
1. source setup.sh
2. lsetup panda
3. cd run
4. source grid\_run.sh

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

## Plotting

Scripts are available in the Results folder to facilitate plotting from the MicroNtuples. TODO: example scripts

