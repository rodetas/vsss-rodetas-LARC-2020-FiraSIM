#!/usr/bin/env bash

INSTALLED=0

INSTALL_CORE() {

    sudo apt-get update
    sudo apt-get -y install git g++ cmake libzmqpp3 libzmqpp-dev
    git clone https://github.com/SIRLab/VSS-Core.git
    cd VSS-Core
    git submodule init;
    git submodule update;
    bash scripts/protos.sh
    mkdir -p build
    cd build
    cmake -DRELEASE=ON ..
    make
    sudo make install
    cd ..
    sudo ./configure.sh
    cd ..
}

INSTALL_SAMPLE() {
    sudo apt-get -y install g++ cmake libboost-all-dev libgtkmm-3.0-dev
    cd net/pb/proto
    sudo sh compile.sh
    cd ..
    cd vssreferee
    sudo sh protobuf.sh
    cd ..
    cd ..
    cd ..
    mkdir build
    cd build
    sudo cmake ..
    sudo make -j4
    team = ""
    while getopts "h?tc:" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    t)  verbose=1
        ;;
    c)  team=$OPTARG
        ;;
    esac
done
    sudo ./SDK-Rodetas -c team

}

INSTALL_CORE;
INSTALL_SAMPLE;
