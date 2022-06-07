# SVJ s-channel Analysis - xAODAnaHelpers

Codes for nTuple creation and evaluation using xAODAnaHelpers, with specialized package extensions for truth information

## Installation

Below is a step-by-step guide on how to use the vanilla xAODAnaHelpers framework to go from DAOD files to NTUPLES. If there are any questions you need answering about steps in this guide, please contact Alison or Joe at: alison.elliot@cern.ch and j.m.m.davies@qmul.ac.uk. 

1. Navigate to the repository https://gitlab.cern.ch/atlas-phys/exot/jdm/ana-exot-2021-19
2. The 'files/' directory has all the files needed for the xAODAnaHelpers installation. Clone the whole repository onto a local machine, lxplus or similar. with something like
`git clone  https://gitlab.cern.ch/atlas-phys/exot/jdm/ana-exot-2021-19.git`
3. Install the xAH package with the install: 
`source install.sh`
   * Notice that the install.sh file has analysis base `AnalysisBase,21.2.120` 
   * If installation gives you an error along the lines of `module os can not be found` then you will need to change the analysis base. To do so, just replace the analysis base with one of the ones listed here: https://xaodanahelpers.readthedocs.io/en/master/ 
4. You should now have `src/` and `build/` directories 
5. Navigate to: `src/xAODAnaHelpers/`
6. Here you will find an `xAODAnaHelpers/` and a `Root/` directory. `xAODAnaHelpers/` has all the .h files in it, `Root/` has all the .cxx files. 
7. For all the .cxx files in the 'files/' directory, copy them into `src/xAODAnaHelpers/Root/`. For all the .h files, copy them into `src/xAODAnaHelpers/xAODAnaHelpers/ `
8. Navigate back up to where your `src/` and `build/` directories are.
9. Force a full recompile by removing the build directory `rm -rf build`, remaking `mkdir build` and compiling `source compile.sh` (note, if you just recompile, it does not seem to pick up the files copied!)
10. Keep `setup_local.sh`, `install.sh` and `compile.sh` in the main directory 
 You are now ready to run! 

### Customising
The algorithm is pretty customisable with the only thing you need to consider is the config file you have. Editing that allows you to replace jet collections, turn off and on reclustering etc. The rule of thumb is, if you t want something included, comment out the relevant name in the last function call of the config file (called `TreeAlgo`)

## Running xAODAnaHelpers Locally
1. To run, navigate to the 'run/' directory.
2. Open `LocalRun_TestStudies.sh` and edit: 
   1. `parentsubmitdir` to be the filepath for your run directory (or wherever you want the output to go) 
   2. `infile` to be the filepath for your DAOD (should be set to cutflow challenge file at the moment)
   3. `configfile` to be the filepath to your `cutflow_signal_DAODtoNTUPLE_mc.py` file (should be set) 
   4. `nevents` to be the number of events you want to run over. Setting this to be larger than the number of events you actually have will just default to running over the entire input file 
2. Now run: `source LocalRun_TestStudies.sh`
3. Your file will be in a directory called: `DAODtoTTREE_<nevents>_Test` in the `run/` directory 
  *. You are interested only in the `.root` file in: `run/DAODtoTTREE_<nevents>_Test/data-tree/` which is the full, populated output*
4. Done! Note: if this is not the first time you are running it, you will need to run: source setup\_local.sh before trying to run again. This must be done at the start of every log in to lxplus or similar.

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

The executable takes 1 or 2 arguemnts; the file tag (`<file_tag>/some_files*.root`) and optionally a path to the input NTuples. By default the input NTuples are assumed to be in the run folder. Usage examples are shown below.
```
./exe/MicroNTupleMaker file_tag
./exe/MicroNTupleMaker file_tag /my/unique/input/path/
```

## Plotting

Scripts are available in the Results folder to facilitate plotting from the MicroNtuples. TODO: example scripts

