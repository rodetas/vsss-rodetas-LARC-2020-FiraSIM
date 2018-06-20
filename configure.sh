#!/usr/bin/env bash

INSTALLED=0

INSTALL_CORE() {

    sudo apt-get update && sudo apt-get upgrade
    sudo apt-get -y install git

    git clone https://github.com/SIRLab/VSS-Core.git
    cd VSS-Core
    sudo bash configure.sh
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

