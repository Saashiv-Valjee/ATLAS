echo "Compiling MicroNTupleMaker..."
g++ -lstdc++fs util/MicroNTupleMaker.C -o exe/MicroNTupleMaker `root-config --cflags --glibs` -lstdc++fs
echo "Done"
