/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "strategy.h"

Strategy* Strategy::instance = NULL;

Strategy::Strategy(){
    main_color = "yellow";
    is_debug = false;
    real_environment = false;
	srand(time(NULL));

	initialize_strategies();
	initialize_robots();
}

void Strategy::init(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name){
	init_sample(main_color, is_debug, real_environment, "localhost", "localhost", "localhost", "name");
	loop();
}

void Strategy::initialize_strategies(){
    strategies["goal"] = new StrategyGoal();
    strategies["attack"] = new StrategyAttack();
    strategies["defense"] = new StrategyDefense();
}

void Strategy::initialize_robots(){
	team["goal"] = &state.robots[0];
    team["attack"] = &state.robots[1];
    team["defense"] = &state.robots[2];
}

void Strategy::loop(){
	while(true){
		// DON'T REMOVE receive_data();
		receive_state();
		// DON'T REMOVE receive_Data();

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

void Strategy::define_function_for_each_robot(){
    
    if (team["attack"]->pose.x > (state.ball.x * 1.1) && 
      !(team["attack"]->pose.x > state.ball.x && team["defense"]->pose.x > state.ball.x) ){

        Robot *aux = team["attack"];
        team["attack"] = team["defense"];
        team["defense"] = aux;
    }
}

void Strategy::apply(){

	// define as funções de cada robô
	define_function_for_each_robot();

	// aplica a estratégia para cada robô
	for(auto it = strategies.begin() ; it != strategies.end() ; it++){
		string function = it->first;
		// envia o robô específico como parâmetro para a estratégia
		(it)->second->apply(team[function]);
	}
}

Strategy* Strategy::getInstance(){
    
    if(instance == NULL){
        instance = new Strategy();
        instance->initialize_strategies();
    }

    return instance;
}