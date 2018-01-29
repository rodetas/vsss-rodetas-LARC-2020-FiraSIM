#include "strategy.h"

Strategy::Strategy(){
    main_color = "yellow";
    is_debug = false;
    real_environment = false;
	srand(time(NULL));

	initialize_strategies();
	initialize_robots();

	timeLastChange = -1;
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
            transmission.send(id["goal"],strategies["goal"]->get_command());
        	transmission.send(id["defense"],strategies["defense"]->get_command());
        	transmission.send(id["attack"], strategies["attack"]->get_command());
		}

		// DON'T REMOVE
		if(is_debug)
			send_debug();
		// DON'T REMOVE'
	}
}

void Strategy::define_function_for_each_robot(){

	btVector3 image_size = btVector3(170,130);

	 if(timeLastChange == -1){

		if (state.robots[id["attack"]].x()*1.3 < state.ball.x() &&
			!	(state.robots[id["attack"]].x() < state.ball.x() &&
				state.robots[id["defense"]].x() < state.ball.x()) &&
			!state.robots[id["attack"]].is_blocked(image_size) &&
			!state.robots[id["defense"]].is_blocked(image_size)){

				int aux = id["attack"];
				id["attack"] = id["defense"];
				id["defense"] = aux;
		}

		float distance_defense_ball = distancePoint(state.robots[id["defense"]].get_position(), state.ball.get_position());
        //float distance_attack_ball = distancePoint(state.robots[id["attack"]].get_position(), state.ball.get_position());

		// na defesa, o mais perto é o atacante
        if(distance_defense_ball < distance_defense_ball && state.ball.x() < image_size.x/2 &&
            !state.robots[id["attack"]].is_blocked(image_size) && !state.robots[id["defense"]].is_blocked(image_size)){

            	int aux = id["attack"];
				id["attack"] = id["defense"];
				id["defense"] = aux;
        }

		if(state.robots[id["attack"]].is_blocked(image_size)){
           	int aux = id["attack"];
            id["attack"] = id["defense"];
            id["defense"] = aux;
        }

		timeLastChange = 60;
	 }

	 if(timeLastChange >= 0) timeLastChange--;
}

void Strategy::apply(){

	// define as funções de cada robô
	//define_function_for_each_robot();

	// aplica a estratégia para cada robô
	//Robot goal = strategies["goal"]->apply(id, state);
	//Robot defense = strategies["defense"]->apply(id, state);
	Robot attack = strategies["attack"]->apply(id, state);

	//debug.robots_final_pose[id["goal"]] = goal.get_target();
	//debug.robots_final_pose[id["defense"]] = defense.get_target();
	debug.robots_final_pose[id["attack"]] = attack.get_target();

	//debug.robots_step_pose[id["goal"]] = goal.get_potencial_direction();
	//debug.robots_step_pose[id["defense"]] = defense.get_potencial_direction();
	debug.robots_step_pose[id["attack"]] = attack.get_potencial_direction();

	//commands[id["goal"]] = strategies["goal"]->get_command();
	//commands[id["defense"]] = strategies["defense"]->get_command();
	commands[id["attack"]] = strategies["attack"]->get_command();
}
