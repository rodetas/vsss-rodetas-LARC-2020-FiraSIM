#include "StrategyBase.h"

StrategyBase::StrategyBase(){
    goal_size  = btVector3(10,40);
    image_size = btVector3(150,130);
}

void StrategyBase::apply(map<string, int> _id, State _state){

    // update states
    setState(_id, _state);

    // update robot in this class
    setRobot(state.robots[id[name]]);

    // define target
    defineTarget(robot);

    // define basic movimentation
    Command movimentationCommand = movimentation.move_players(robot, target);

    // define strategy
    Command strategyCommand = strategy(robot, movimentationCommand);

    // define command
    defineCommand(strategyCommand);    
} 

void StrategyBase::move(map<string, int> _id, State _state){
    
    // update states
    setState(_id, _state);

    // update robot in this class
    setRobot(state.robots[id[name]]);

    // define basic movimentation
    Command movimentationCommand = movimentation.move_players(robot, target);

    // define strategy
    Command strategyCommand = stopStrategy(strategyCommand);
    
    // define command
    defineCommand(strategyCommand); 
}

 Command StrategyBase::cornerStrategy(Command command){
    Command c = command;

	if (robot.is_board(image_size) && robot.is_stopped()){      

        // girar caso robo esteja preso de frente pra parede
        if (robot.cos_from(state.ball.pose) > -0.9 && robot.cos_from(state.ball.pose) < 0.9) {
            if (robot.sin_from(state.ball.pose) > 0) {
                c = movimentation.turn_right(100, 100);
            } else {
                c = movimentation.turn_left(100, 100);
            }
        } 
        
        // girar caso robo prenda a bola na parede
        if (robot.distance_from(state.ball.pose) < robot.get_radius()*1.5) {

            if (robot.y() > (image_size.y/2)){
                c = movimentation.turn_left(255, 255);	
            } else {
                c = movimentation.turn_right(255, 255);
            }
        }
    }

    return c;
}

Command StrategyBase::stopStrategy(Command _command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = _command;
    float maxDistance = robot.get_radius() * (3);
	float distanceTarget = robot.distance_from(target);

/* 	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = robot.get_radius() * (6);
	}
 */

	if(distanceTarget < maxDistance){
		c.left  = c.left  * (distanceTarget/maxDistance);
		c.right = c.right * (distanceTarget/maxDistance);
	}

	if(distanceTarget < robot.get_radius()){

        if (robot.cos_from(state.ball.get_projection()) < -0.8 || robot.cos_from(state.ball.get_projection()) > 0.8) {
            c = movimentation.stop();
 
        } else {

            if (robot.sin_from(state.ball.get_position()) > 0) {
                c = movimentation.turn_right(10, 10);
            } else {
                c = movimentation.turn_left(10, 10);
            }
        }
    }

    return c;
}

Command StrategyBase::collisionStrategy(Command _command){   
}

Command StrategyBase::blockedStrategy(Command _command){
}

Command StrategyBase::kickStrategy(Command _command){
}

void StrategyBase::setRobot(Robot _robot){
    robot = _robot;
}

void StrategyBase::setState(map<string, int> _id, State _state){
    id = _id;    
    state = _state;    
}

Robot StrategyBase::getRobot(string func){
    return state.robots[id[func]];
}

Command StrategyBase::getCommand(){
    return command;
}