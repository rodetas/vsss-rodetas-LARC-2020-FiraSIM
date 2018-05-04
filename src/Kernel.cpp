#include <Kernel.h>
#include <strategies/RobotStrategyDefender.h>
#include <strategies/RobotStrategyGoal.h>

Kernel::Kernel(){
	srand(time(NULL));
}

void Kernel::loop(){

    StateReceiverAdapter receiveInterface;
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);

    vector<RodetasRobot> robots(3);
    vector<Command> commands(3);

    RodetasState state;
    Debug debug;

    robots[2].setStrategy(new RobotStrategyAttack());
    robots[1].setStrategy(new RobotStrategyDefender());
    robots[0].setStrategy(new RobotStrategyGoal());

	while(true){

        // method which waits and receives a new state from simulator or vision
        //@TODO jogar parametros para o construtor da classe StateReceiveAdapter
		state = receiveInterface.receiveState(Config::changeSide, Config::teamColor);

        for(unsigned int i=0 ; i<robots.size() ; i++){
            RodetasRobot& robot = robots[i];

            robot.updateSelfState(state.robots[i]);
            robot.updateState(state);
            robot.calcAction();

            commands[i] = robot.getCommand();

            debug.robotsFinalPose[i] = robot.getRobotDebug().robotFinalPose;
            debug.robotsStepPose[i] = robot.getRobotDebug().robotStepPose;
            debug.robotsPath[i] = robot.getRobotDebug().path;

        }

		sendInterface.sendCommands(commands);
		debugInterface.sendDebug(debug);
	}
}

void Kernel::define_function_for_each_robot(){

//	btVector3 image_size = btVector3(170,130);
//
//	 if(timeLastChange == -1){
//
//		if (state.robots[id["attack"]].x*1.3 < state.ball.x &&
//			!	(state.robots[id["attack"]].x < state.ball.x &&
//				state.robots[id["defense"]].x < state.ball.x) &&
//			!state.robots[id["attack"]].is_blocked(image_size) &&
//			!state.robots[id["defense"]].is_blocked(image_size)){
//
//				int aux = id["attack"];
//				id["attack"] = id["defense"];
//				id["defense"] = aux;
//		}
//
//		float distance_defense_ball = distancePoint(state.robots[id["defense"]].get_position(), state.ball.get_position());
//        //float distance_attack_ball = distancePoint(state.robots[id["attack"]].get_position(), state.ball.get_position());
//
//		// na defesa, o mais perto é o atacante
//        if(distance_defense_ball < distance_defense_ball && state.ball.x() < image_size.x/2 &&
//            !state.robots[id["attack"]].is_blocked(image_size) && !state.robots[id["defense"]].is_blocked(image_size)){
//
//            	int aux = id["attack"];
//				id["attack"] = id["defense"];
//				id["defense"] = aux;
//        }
//
//		if(state.robots[id["attack"]].is_blocked(image_size)){
//           	int aux = id["attack"];
//            id["attack"] = id["defense"];
//            id["defense"] = aux;
//        }
//
//		timeLastChange = 60;
//	 }
//
//	 if(timeLastChange >= 0) timeLastChange--;
}