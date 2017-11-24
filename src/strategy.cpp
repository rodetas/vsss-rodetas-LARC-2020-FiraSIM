#include "strategy.h"

Strategy::Strategy(){
    main_color = "yellow";
    is_debug = false;
    real_environment = false;
	srand(time(NULL));

	initialize_strategies();
	initialize_robots();
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

		} else {
			// Put your transmission code here
		}

		// DON'T REMOVE
		if(is_debug)
			send_debug();
		// DON'T REMOVE'
	}
}

void Strategy::define_function_for_each_robot(){
    
    if (state.robots[id["attack"]].x() > (state.ball.x() * 1.1) && 
      !(state.robots[id["attack"]].x() > state.ball.x() && state.robots[id["defense"]].x() > state.ball.x()) ){

        /* int aux = id["attack"];
        id["attack"] = id["defense"];
        id["defense"] = aux; */
    }
}

void Strategy::apply(){

	// define as funções de cada robô
	define_function_for_each_robot();

	// aplica a estratégia para cada robô
	//strategies["goal"]->apply(id, state);
	//strategies["defense"]->apply(id, state);
	Robot attack = strategies["attack"]->apply(id, state);

	debug.robots_final_pose[id["attack"]] = attack.get_target();

	//commands[id["goal"]] = strategies["goal"]->get_command();
	//commands[id["defense"]] = strategies["defense"]->get_command();
	commands[id["attack"]] = strategies["attack"]->get_command();
}