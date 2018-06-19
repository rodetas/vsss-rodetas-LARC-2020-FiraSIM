//
// Created by manoel on 23/04/18.
//

#include "Communication/CommandSendAdapter.h"

CommandSendAdapter::CommandSendAdapter(vss::TeamType teamColor, bool isRealEnvironment) {
    this->isRealEnvironment = isRealEnvironment;
    this->teamColor = teamColor;

    createSocketSendCommand();
}

void CommandSendAdapter::createSocketSendCommand() {
    interfaceSend.createSocket(teamColor);
}

void CommandSendAdapter::sendCommands(vector<vss::WheelsCommand> commands, bool isPlaying, bool isTestingTransmission) {

    if(!isRealEnvironment) {
        // sends commands to simulator

        vss::Command vssCommand;
        vssCommand.commands.insert(vssCommand.commands.begin(), commands.begin(), commands.end());

        interfaceSend.sendCommand(vssCommand);

    } else if(isPlaying) {
        // sends commands to xbee
        transmission.send(2, commands[0]);
//        transmission.send(1, commands[1]);
//        transmission.send(2, commands[2]);
    } else if(isTestingTransmission){
        // send commands to test robots

    } else {

    }
}

