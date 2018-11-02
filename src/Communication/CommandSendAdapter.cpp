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

void CommandSendAdapter::sendCommands(std::vector<RodetasRobot> robots, bool isPlaying, bool isTestingTransmission) {

    std::vector<vss::WheelsCommand> commands;
    for (auto robot : robots) {
        commands.push_back(robot.getCommand());
    }

    if(not isRealEnvironment and isPlaying) {
        // sends commands to simulator

        vss::Command vssCommand;
        vssCommand.commands.insert(vssCommand.commands.begin(), commands.begin(), commands.end());

        interfaceSend.sendCommand(vssCommand);

    } else if(isPlaying) {
        for(auto robot : robots){
            transmission.send(robot.getId(), robot.getCommand());
        }

    } else if(isTestingTransmission){
        vss::WheelsCommand turnRightCommand(60,-60);
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
