mkdir build
cd src
asetup AnalysisBase,22.2.75,here
cd ../build
cmake ../src
make
source x86*/setup.sh
cd ..
