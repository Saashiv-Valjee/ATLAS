FROM atlas/analysisbase:21.2.91

USER root

Add . /usr/fourb/src/MultiBTaggedAlgo

RUN mkdir /usr/fourb/build && \
    cd /usr/fourb/src && \
    source /home/atlas/release_setup.sh && \
    cp ./MultiBTaggedAlgo/MasterCMake CMakeLists.txt && \
    cd /usr/fourb/build && \
    cmake ../src && \
    make && \ 
    mkdir /usr/fourb/run 

