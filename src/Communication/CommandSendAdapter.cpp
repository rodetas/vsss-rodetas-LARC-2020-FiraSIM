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

        vss::Command vssCommand;
        vssCommand.commands.insert(vssCommand.commands.begin(), commands.begin(), commands.end());

        interfaceSend.sendCommand(vssCommand);

    } else if(isPlaying) {
        transmission.send(2,commands[0]);
//        	transmission.send(id["defense"],strategies["defense"]->get_command());
//        	transmission.send(id["attack"], strategies["attack"]->get_command());
    } else if(isTestingTransmission){

    } else {

    }
}

