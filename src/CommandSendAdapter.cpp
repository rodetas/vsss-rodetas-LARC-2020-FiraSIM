//
// Created by manoel on 23/04/18.
//

#include "CommandSendAdapter.h"

CommandSendAdapter::CommandSendAdapter(string teamColor, bool isRealEnvironment) {
    this->isRealEnvironment = isRealEnvironment;
    this->teamColor = teamColor;

    createSocketSendCommand();
}

void CommandSendAdapter::createSocketSendCommand() {

    if(teamColor == "yellow"){
        interfaceSend.createSendCommandsTeam1(&this->globalCommands);
    } else {
        interfaceSend.createSendCommandsTeam2(&this->globalCommands);
    }

}

void CommandSendAdapter::sendCommands(vector<common::Command> commands, bool isPlaying, bool isTestingTransmission) {

    if(!isRealEnvironment) {
        globalCommands = vss_command::Global_Commands();

        if (teamColor == "yellow") {
            globalCommands.set_is_team_yellow(true);
        } else {
            globalCommands.set_is_team_yellow(false);
        }

        for (int i = 0; i < 3; i++) {
            vss_command::Robot_Command *robot = globalCommands.add_robot_commands();
            robot->set_id(i);
            robot->set_left_vel(commands[i].left);
            robot->set_right_vel(commands[i].right);
        }

        if (teamColor == "yellow") {
            interfaceSend.sendCommandTeam1();
        } else {
            interfaceSend.sendCommandTeam2();
        }

    } else if (isPlaying) {
        //@TODO: invocar funcoes do transmission
//          transmission.send(id["goal"],strategies["goal"]->get_command());
//        	transmission.send(id["defense"],strategies["defense"]->get_command());
//        	transmission.send(id["attack"], strategies["attack"]->get_command());
    } else if (isTestingTransmission) {
        // @TODO: send transmission test command
    } else {
        // @TODO send stopped command
    }
}

