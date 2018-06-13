//
// Created by manoel on 23/04/18.
//

#include "CommandSendAdapter.h"

CommandSendAdapter::CommandSendAdapter(TeamColor::Color teamColor,bool isRealEnvironment) {
    this->isRealEnvironment = isRealEnvironment;
    this->teamColor = teamColor;

    createSocketSendCommand();
}

void CommandSendAdapter::createSocketSendCommand() {

    if(teamColor == TeamColor::YELLOW){
        interfaceSend.createSendCommandsTeam1(&this->globalCommands);
    } else {
        interfaceSend.createSendCommandsTeam2(&this->globalCommands);
    }

}

void CommandSendAdapter::sendCommands(vector<common::Command> commands) {

    if(!isRealEnvironment) {
        globalCommands = vss_command::Global_Commands();

        if (teamColor == TeamColor::YELLOW) {
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

        if (teamColor == TeamColor::YELLOW) {
            interfaceSend.sendCommandTeam1();
        } else {
            interfaceSend.sendCommandTeam2();
        }

    } else {
        //@TODO: invocar funcoes do transmission
//            transmission.send(id["goal"],strategies["goal"]->get_command());
//        	transmission.send(id["defense"],strategies["defense"]->get_command());
//        	transmission.send(id["attack"], strategies["attack"]->get_command());
    }
}

