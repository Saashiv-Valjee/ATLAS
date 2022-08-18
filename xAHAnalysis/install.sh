mkdir build
cd src
#asetup AnalysisBase,22.2.75,here
AnalysisBase,21.2.120
cd ../build
cmake ../src
make
source x86*/setup.sh
cd ..
