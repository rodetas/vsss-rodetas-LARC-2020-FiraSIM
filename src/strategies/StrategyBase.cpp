#include "StrategyBase.h"

StrategyBase::StrategyBase(){
    
}

void StrategyBase::apply(map<string, int> _id, State _state){
    // update robot
    setState(_state);
    setIds(_id);
    setRobot(_state.robots[_id[name]]);


    // define target
    defineTarget(robot);
    
    // define basic movimentation
    Command movimentationCommand = movimentation.movePlayers(robot);

    // define strategy
    Command strategyCommand = strategy(robot, movimentationCommand);
    
    // adjust final pwm
    Command finalPwm = movimentation.progressiveAcell(robot, strategyCommand);
    
    // define command
    defineCommand(finalPwm);
} 

void StrategyBase::move(Robot robot){
    /* // update robot
    setRobot(robot);

    // define basic movimentation
    Command movimentationCommand = movimentation.movePlayers(robot);

    // define strategy
    Command strategyCommand = stopStrategy(strategyCommand);

    // adjust final pwm
    Command finalPwm = movimentation.progressiveAcell(robot, strategyCommand);
    
    // define command
    defineCommand(finalPwm);  */
}

 Command StrategyBase::cornerStrategy(Command command){
    // movement along the corners
    /* Command c = command;

	if (robot->isBoard() && robot->isStopped()){
        
        // girar caso robo esteja preso de frente pra parede
        if (robot->cosFrom(data->getBall()->getPosition()) > -0.9 && robot->cosFrom(data->getBall()->getPosition()) < 0.9) {
            if (robot->sinFrom(data->getBall()->getPosition()) > 0) {
                c = movimentation.turn(robot, data->getBall()->getPosition(), RIGHT_MOVE);
            } else {
                c = movimentation.turn(robot, data->getBall()->getPosition(), LEFT_MOVE);
            }
        } 
        
        // girar caso robo prenda a bola na parede
        if (robot->distanceFrom(data->getBall()->getPosition()) < robot->getRadius()*1.5) {

            if (robot->y() > (rodetas::imageSize.y/2)){
                c = movimentation.turnLeft(255, 255);	
            } else {
                c = movimentation.turnRight(255, 255);
            }
        }
    }

    return c; */
}

Command StrategyBase::stopStrategy(Command _command){
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    /* Command c = _command;
    float maxDistance = robot->getRadius()*3;
	float distanceTarget = robot->distanceFrom(robot->getTarget());
	
	if(robot->getVelocity() > rodetas::imageSize.x*0.05){
		maxDistance = robot->getRadius()*6;
	}

	if(distanceTarget < maxDistance){
		c.pwm1 = c.pwm1*(distanceTarget/maxDistance);
		c.pwm2 = c.pwm2*(distanceTarget/maxDistance);
	}

	if(distanceTarget < robot->getRadius()){

        if (robot->cosFrom(data->getBall()->getBallProjection()) < -0.8 || robot->cosFrom(data->getBall()->getBallProjection()) > 0.8) {
            c = movimentation.stop();
 
        } else {

            if (robot->sinFrom(data->getBall()->getPosition()) > 0) {
                //c = movimentation.turnRight(pwm, pwm);
                c = movimentation.turn(robot, data->getBall()->getBallProjection(), RIGHT_MOVE);
            } else {
                //c = movimentation.turnLeft(pwm, pwm);
                c = movimentation.turn(robot, data->getBall()->getBallProjection(), LEFT_MOVE);
            }
        }
    }

    return c; */
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

void StrategyBase::setState(State _state){
    state = _state;    
}

void StrategyBase::setIds(map<string, int> _id){
    id = _id;
}

Robot StrategyBase::getRobot(string func){
    return state.robots[id[func]];
}