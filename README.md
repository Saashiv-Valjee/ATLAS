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

First, create a directory called MicroNTuples where your output will live, and a directory for the executable.
```
cd MicroNTupleMaker
mkdir MicroNTuples
mkdir exe
```

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

## Plotting

Scripts are available in the Results folder to facilitate plotting from the MicroNtuples. TODO: example scripts

