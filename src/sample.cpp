/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <sample.h>

void Sample::init_sample(string team_color, bool is_debug, bool real_environment){
    
	this->is_debug = is_debug;
    this->team_color = team_color;
    this->real_environment = real_environment;
	this->ip_send_debug = "tcp://localhost";
	this->ip_send_command = "tcp://localhost";
	this->ip_receive_state = "tcp://localhost:5555";

    interface_receive.createSocketReceiveState(&global_state, this->ip_receive_state);

	if(team_color == "yellow"){
		this->ip_send_command += ":5556";
		interface_send.createSendCommandsTeam1(&global_commands, this->ip_send_command);
		
		if(is_debug){
			this->ip_send_debug += ":5558";
			interface_debug.createSendDebugTeam1(&global_debug, this->ip_send_debug);
		}

	}else{
		this->ip_send_command += ":5557";
		interface_send.createSendCommandsTeam2(&global_commands, this->ip_send_command);

		if(is_debug){
			this->ip_send_debug += ":5559";
			interface_debug.createSendDebugTeam2(&global_debug, this->ip_send_debug);
		}
	}
}

void Sample::receive_state(){
    interface_receive.receiveState();
	state = State::Global_State2State(global_state, team_color);
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

void Sample::send_debug(){
	global_debug = vss_debug::Global_Debug();
	
	// Add step pose, if exists
	for(int i = 0 ; i < 3 ; i++){
		vss_debug::Pose *steps = global_debug.add_step_poses();
		steps->set_id(i);
		steps->set_x(debug.robots_step_pose[i].x);
		steps->set_y(debug.robots_step_pose[i].y);
		steps->set_yaw(debug.robots_step_pose[i].z);
	}

	// Add final pose, if exists
	for(int i = 0 ; i < 3 ; i++){
		vss_debug::Pose *finals = global_debug.add_final_poses();
		finals->set_id(i);
		finals->set_x(debug.robots_final_pose[i].x);
		finals->set_y(debug.robots_final_pose[i].y);
		finals->set_yaw(debug.robots_final_pose[i].z);
	}

	for(int i = 0 ; i < 3 ; i++){
		vss_debug::Path *paths = global_debug.add_paths();
		paths->set_id(i);
		for(uint j = 0 ; j < debug.robots_path[i].poses.size() ; j++){
			vss_debug::Pose *poses = paths->add_poses();
			poses->set_id(i);
			poses->set_x(debug.robots_path[i].poses.at(j).x);
			poses->set_y(debug.robots_path[i].poses.at(j).y);
			poses->set_yaw(debug.robots_path[i].poses.at(j).z);
		}
	}

	if(team_color == "yellow"){
		interface_debug.sendDebugTeam1();
	}else{
		interface_debug.sendDebugTeam2();
	}	
}