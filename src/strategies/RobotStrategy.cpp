//
// Created by manoel on 17/04/18.
//

#include <RobotStrategy.h>

RobotStrategy::RobotStrategy() {
    movimentation = new Movimentation();
}

Command RobotStrategy::applyStrategy(RobotState r, RodetasState s) {
    this->robot = r;
    this->state = s;

    // defines robot's target
    this->target = this->defineTarget();

    // defines robot's pwm
    Command c = movimentation->move_players(robot, target);

    // defines specific strategy such as corner strategy or kick strategy - can be applied or not
    c = this->specificStrategy(c);

    return c;
}

Command RobotStrategy::corner_strategy(Command c) {
    if (strategyBase.isBoard() && strategyBase.isStopped()){

        // girar caso robo esteja preso de frente pra parede
        if (robot.cosFrom(state.ball.position) > -0.9 && robot.cosFrom(state.ball.position) < 0.9) {
            if (robot.sinFrom(state.ball.position) > 0) {
                c = movimentation->turn_right(50,30);
            } else {
                c = movimentation->turn_left(50,50);
            }
//            cout << "preso pra parede" << endl;
        }

        // girar caso robo prenda a bola na parede - 8 cm
        if (robot.distanceFrom(state.ball.position) < (8) ) {

            if (robot.position.y < (imageSize.y/2)){
                c = movimentation->turn_left(60,60);
            } else {
                c = movimentation->turn_right(60,60);
            }
//            cout << "preso com bola" << endl;
        }
    }

    return c;
}

Command RobotStrategy::stop_strategy(Command c) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    float max_distance = 12; // 12 cm
    float distance_target = robot.distanceFrom(target);

/* 	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		max_distance = 24; // 24 cm
	}
*/

    if(distance_target < max_distance){
        c.left  = c.left  * (distance_target/max_distance);
        c.right = c.right * (distance_target/max_distance);
    }

    if(distance_target < 4){

        if (robot.cosFrom(ballProjection) < -0.8 || robot.cosFrom(ballProjection) > 0.8) {
            c = movimentation->stop();

        } else {

            if (robot.sinFrom(state.ball.position) > 0) {
                c = movimentation->turn_right(10, 10);
            } else {
                c = movimentation->turn_left(10, 10);
            }
        }
    }

    return c;
}

Command RobotStrategy::kick_strategy(Command c) {
    return c;
}

Command RobotStrategy::blocked_strategy(Command c) {
    return c;
}

Command RobotStrategy::getCommand() {
    return this->command;
}

btVector3 RobotStrategy::getFinalPose() {
    return this->target;
}

btVector3 RobotStrategy::getStepPose() {
    return this->stepPose;
}

Path RobotStrategy::getPath() {
    return this->path;
}