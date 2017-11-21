/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "strategy.h"

Strategy::Strategy(){
    main_color = "yellow";
    is_debug = false;
    real_environment = false;
	robot_radius = 8.0;
	distance_to_stop = 5.0;
	changePose = true;
	srand(time(NULL));
}

void Strategy::init(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name){
	init_sample(main_color, is_debug, real_environment, ip_receive_state, ip_send_debug, ip_send_command, name);
	loop();
}

void Strategy::initialize_strategies(){
    strategies["goal"] = new StrategyGoal();
    strategies["attack"] = new StrategyAttack();
    strategies["defense"] = new StrategyDefense();
}

void Strategy::initialize_robots(){
   /*  team["goal"] = state.robots[0];
    team["attack"] = state.robots[1];
    team["defense"] = state.robots[2]; */
}

void Strategy::loop(){
	while(true){
		// DON'T REMOVE receive_data();
		receive_state();
		// DON'T REMOVE receive_Data();'
				
		if(!real_environment){
			// DON'T REMOVE send_data();
			send_commands();
			// DON'T REMOVE send_data();
		}else{
			// Put your transmission code here
		}

		// DON'T REMOVE
		if(is_debug)
			send_debug();
		// DON'T REMOVE'
	}
}

void Strategy::convert_receive_state(){
	team["goal"]->pose = state.robots[0].pose;
	team["attack"]->pose = state.robots[1].pose;
	team["defense"]->pose = state.robots[2].pose;
	
}

void Strategy::convert_send_commands(){
	
}
