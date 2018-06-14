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

void CommandSendAdapter::sendCommands(vector<common::Command> commands) {

    if(!isRealEnvironment) {

        vss::Command vssCommand;
        vssCommand.id = 0;

        for(unsigned int i=0 ; i<commands.size() ; i++){
            vssCommand.commands.push_back(commandToWheelsCommand(i, commands[i]));
        }

        interfaceSend.sendCommand(vssCommand);

    } else {
        //@TODO: invocar funcoes do transmission
        transmission.send(2,commands[0]);
//        	transmission.send(id["defense"],strategies["defense"]->get_command());
//        	transmission.send(id["attack"], strategies["attack"]->get_command());
    }
}

vss::WheelsCommand CommandSendAdapter::commandToWheelsCommand(int id, Command command){

    vss::WheelsCommand wheelsCommand;
    wheelsCommand.id = id;
    wheelsCommand.leftVel = command.left;
    wheelsCommand.rightVel = command.right;

    return wheelsCommand;
}

