//
// Created by manoel on 16/04/18.
//

#include <Communication/DebugSenderAdapter.h>

DebugSendAdapter::DebugSendAdapter(vss::TeamType teamColor, bool isDebug) {
    this->teamColor = teamColor;
    this->isDebug = isDebug;

    if(isDebug)
        createSocketDebug();
}

void DebugSendAdapter::createSocketDebug() {
    interfaceDebug.createSocket(teamColor);
}

void DebugSendAdapter::sendDebug(vss::Debug debug) {
    if(isDebug)
        interfaceDebug.sendDebug(debug);
}




