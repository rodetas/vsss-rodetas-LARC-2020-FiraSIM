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
	id["goal"] = 0;
	id["attack"] = 1;
	id["defense"] = 2;
}

void Strategy::loop(){
	while(true){
		
		receive_state();
		
		apply();

		if(!real_environment){
			send_commands();

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
    
    if (state.robots[id["attack"]].pose.x > (state.ball.pose.x * 1.1) && 
      !(state.robots[id["attack"]].pose.x > state.ball.pose.x && state.robots[id["defense"]].pose.x > state.ball.pose.x) ){

        int aux = id["attack"];
        id["attack"] = id["defense"];
        id["defense"] = aux;
    }
}

void Strategy::apply(){

	// define as funções de cada robô
	define_function_for_each_robot();

	// aplica a estratégia para cada robô
	strategies["goal"]->apply(id, state);
	strategies["attack"]->apply(id, state);
	strategies["defense"]->apply(id, state);
	
//	cout << strategies["attack"]->getCommand().left << " " << strategies["attack"]->getCommand().right << endl;
	commands[id["attack"]] = strategies["attack"]->getCommand();
}

Strategy* Strategy::getInstance(){
    
    if(instance == NULL){
        instance = new Strategy();
        instance->initialize_strategies();
    }

    return instance;
}