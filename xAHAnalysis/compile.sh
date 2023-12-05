cd build
cmake -DATLAS_PACKAGE_FILTER_FILE=../package_filters_example.txt ../localRelease/athena/Projects/WorkDir/
make
source x86*/setup.sh
cd ..
