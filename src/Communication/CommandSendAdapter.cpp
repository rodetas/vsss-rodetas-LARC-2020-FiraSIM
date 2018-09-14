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

    if(not isRealEnvironment and isPlaying) {
        // sends commands to simulator

        vss::Command vssCommand;
        vssCommand.commands.insert(vssCommand.commands.begin(), commands.begin(), commands.end());

        interfaceSend.sendCommand(vssCommand);

    } else if(isPlaying) {
        transmission.send(2, commands[0]);
//        transmission.send(1, commands[1]);
//        transmission.send(2, commands[2]);

    } else if(isTestingTransmission){
        vss::WheelsCommand turnRightCommand(40,-40);
        for(int i=0 ; i<3 ; i++){
            transmission.send(i, turnRightCommand);
        }

    } else {
        if(isRealEnvironment) {
            vss::WheelsCommand stopCommand(0, 0);
            for (int i = 0; i < 3; i++) {
                transmission.send(i, stopCommand);
            }
        } else {
            vss::Command vssCommand;
            vss::WheelsCommand nullCommand;
            vssCommand.commands.resize(3, nullCommand);

            interfaceSend.sendCommand(vssCommand);
        }
    }
}
