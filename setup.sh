# cd to where this script is
export thisismydir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $thisismydir

cd src

if [[ $HOSTNAME = lxplus* ]]; then
    export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
    source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
    lsetup cmake
    lsetup "asetup AnalysisBase,21.2.120,here"
else
    # aurora etc
    export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
    source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
    lsetup cmake
    lsetup python
    asetup AnalysisBase,21.2.120,here
fi

lsetup git

cd ../run
source ../build/*/setup.sh
