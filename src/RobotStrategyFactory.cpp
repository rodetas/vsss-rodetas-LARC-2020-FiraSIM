//
// Created by manoel on 24/04/18.
//

#include "RobotStrategyFactory.h"

RobotStrategyFactory::RobotStrategyFactory() {
    imageSize = {170,130};
}

void RobotStrategyFactory::manage(RodetasState state) {

//	 if(timeLastChange == -1){
//
//		if (state.robots[id["attack"]].x*1.3 < state.ball.position.x &&
//			!	(state.robots[id["attack"]].x < state.ball.position.x &&
//				state.robots[id["defense"]].x < state.ball.position.x) &&
//			!state.robots[id["attack"]].is_blocked(imageSize) &&
//			!state.robots[id["defense"]].is_blocked(imageSize)){
//
//				int aux = id["attack"];
//				id["attack"] = id["defense"];
//				id["defense"] = aux;
//		}
//
//		float distance_defense_ball = Math::distancePoint(state.robots[id["defense"]].get_position(), state.ball.getPosition());
//        //float distance_attack_ball = distancePoint(state.robots[id["attack"]].get_position(), state.ball.get_position());
//
//		// na defesa, o mais perto é o atacante
//        if(distance_defense_ball < distance_defense_ball && state.ball.position.x < imageSize.x/2 &&
//            !state.robots[id["attack"]].is_blocked(imageSize) && !state.robots[id["defense"]].is_blocked(imageSize)){
//
//            	int aux = id["attack"];
//				id["attack"] = id["defense"];
//				id["defense"] = aux;
//        }
//
//		if(state.robots[id["attack"]].is_blocked(imageSize)){
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

RobotStrategy* RobotStrategyFactory::getStrategyForRobot(int i) {
    return 0;
}
