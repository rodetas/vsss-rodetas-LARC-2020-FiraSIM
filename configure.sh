#!/usr/bin/env bash

INSTALLED=0

INSTALL_CORE() {

    sudo apt-get update
    sudo apt-get -y install git g++ cmake libzmqpp3 libzmqpp-dev protobuf-compiler libprotobuf-dev
    git clone https://github.com/SIRLab/VSS-Core.git
    cd VSS-Core
    git submodule init;
    git submodule update;
    bash scripts/protos.sh
    mkdir -p build
    cd build
    cmake ..
    make
    cd ..
}

INSTALL_SAMPLE() {
    cd ..
    sudo apt-get -y install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev gtkmm-2.4
}

CMAKE () {
    mkdir build
    cd build
    cmake ..
}

INSTALL_CORE;
INSTALL_SAMPLE;
CMAKE;

