#!/usr/bin/env bash

INSTALLED=0

INSTALL_CORE() {

    apt-get update && apt-get upgrade
    apt-get -y install git

    git clone https://github.com/SIRLab/VSS-Core.git
    cd VSS-Core
    bash configure.sh
}

INSTALL_SAMPLE() {
    apt-get -y install pkg-config
    apt-get -y install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev gtkmm-2.4
    INSTALLED=1
}

CMAKE () {
    mkdir build
    cd build
    cmake ..
}

