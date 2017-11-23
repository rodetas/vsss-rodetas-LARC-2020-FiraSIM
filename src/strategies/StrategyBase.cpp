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
    Command movimentationCommand = movimentation.movePlayers(robot, target);

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
    Command movimentationCommand = movimentation.movePlayers(robot, target);

    // define strategy
    Command strategyCommand = stopStrategy(strategyCommand);
    
    // define command
    defineCommand(strategyCommand); 
}

 Command StrategyBase::cornerStrategy(Command command){

    Command c = command;

	if (robot.isBoard(image_size) && robot.isStopped()){      

        // girar caso robo esteja preso de frente pra parede
        if (robot.cosFrom(state.ball.pose) > -0.9 && robot.cosFrom(state.ball.pose) < 0.9) {
            if (robot.sinFrom(state.ball.pose) > 0) {
                c = movimentation.turnRight(100, 100);
            } else {
                c = movimentation.turnLeft(100, 100);
            }
        } 
        
        // girar caso robo prenda a bola na parede
        if (robot.distanceFrom(state.ball.pose) < robot.getRadius()*1.5) {

            if (robot.y() > (image_size.y/2)){
                c = movimentation.turnLeft(255, 255);	
            } else {
                c = movimentation.turnRight(255, 255);
            }
        }
    }

    return c;
}

Command StrategyBase::stopStrategy(Command _command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    Command c = _command;
    float maxDistance = robot.getRadius() * (3);
	float distanceTarget = robot.distanceFrom(target);

/* 	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = robot.getRadius() * (6);
	}
 */

	if(distanceTarget < maxDistance){
		c.left  = c.left  * (distanceTarget/maxDistance);
		c.right = c.right * (distanceTarget/maxDistance);
	}

	if(distanceTarget < robot.getRadius()){

        if (robot.cosFrom(state.ball.getProjection()) < -0.8 || robot.cosFrom(state.ball.getProjection()) > 0.8) {
            c = movimentation.stop();
 
        } else {

            if (robot.sinFrom(state.ball.getPosition()) > 0) {
                c = movimentation.turnRight(10, 10);
            } else {
                c = movimentation.turnLeft(10, 10);
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