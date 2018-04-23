/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <sample.h>
#include <config.h>

void Sample::init_sample(string team_color, bool real_environment){
    
    this->team_color = team_color;
    this->real_environment = real_environment;
	this->ip_send_command = "tcp://localhost";

	if(team_color == "yellow"){
		this->ip_send_command += ":5556";
		interface_send.createSendCommandsTeam1(&global_commands, this->ip_send_command);

	} else {
		this->ip_send_command += ":5557";
		interface_send.createSendCommandsTeam2(&global_commands, this->ip_send_command);

	}
}

void Sample::send_commands(){
    global_commands = vss_command::Global_Commands();

	if(team_color == "yellow"){
		global_commands.set_is_team_yellow(true);
	}else{
		global_commands.set_is_team_yellow(false);
	}

	for(int i = 0 ; i < 3 ; i++){
		vss_command::Robot_Command *robot = global_commands.add_robot_commands();
		robot->set_id(i);
		robot->set_left_vel(commands[i].left);
		robot->set_right_vel(commands[i].right);
	}

    if(team_color == "yellow"){
        interface_send.sendCommandTeam1();
    }else{
        interface_send.sendCommandTeam2();
    }	
}