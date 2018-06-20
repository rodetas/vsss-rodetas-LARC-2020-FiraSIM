#!/usr/bin/env bash

INSTALLED=0

INSTALL_CORE() {

    sudo apt-get update
    sudo apt-get -y install git
    echo "Installing git"
    sleep 2
    git clone https://github.com/SIRLab/VSS-Core.git
    cd VSS-Core
    echo "Configuring core"
    sleep 2
    sudo bash configure.sh
    echo "configured"
    sleep 2
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

