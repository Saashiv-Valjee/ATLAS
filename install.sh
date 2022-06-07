mkdir build src
cd src
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
lsetup git
git clone https://github.com/UCATLAS/xAODAnaHelpers
lsetup cmake
lsetup "asetup AnalysisBase,21.2.120,here"
cd ../build
cmake ../src
make
source */setup.sh
cd ..
echo "Finished running install.sh"
