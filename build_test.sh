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
    cmake -DRELEASE=ON ..
    make
    sudo make install
    cd ..
    sudo ./configure.sh
    cd ..
}

INSTALL_SAMPLE() {
    sudo apt-get -y install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev libgtkmm-3.0-dev

    mkdir build
    cd build
    cmake ..
    make
}

INSTALL_CORE;
INSTALL_SAMPLE;
