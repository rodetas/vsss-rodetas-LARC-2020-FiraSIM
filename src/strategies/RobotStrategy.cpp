//
// Created by manoel on 17/04/18.
//

#include <RobotStrategy.h>

RobotStrategy::RobotStrategy() {
    movimentation = new Movimentation();
}

Command RobotStrategy::applyStrategy(RobotState r, RodetasState s, RobotStrategyBase base) {
    this->robot = r;
    this->state = s;
    this->strategyBase = base;

    // defines robot's target,
    target = this->defineTarget();

    float fi = this->applyUnivectorField(target);

    // defines robot's pwm
    command = movimentation->movePlayers(robot, target, fi);

    // defines specific strategy such as corner strategy or kick strategy - can be applied or not
    command = this->specificStrategy(command);

    return command;
}

Command RobotStrategy::cornerStrategy(Command c) {
    if (strategyBase.isBoard() && strategyBase.isStopped()) {

        // girar caso robo esteja preso de frente pra parede
        if (robot.cosFrom(state.ball.position) > -0.9 && robot.cosFrom(state.ball.position) < 0.9) {
            if (robot.sinFrom(state.ball.position) > 0) {
                c = movimentation->turnRight(50, 30);
            } else {
                c = movimentation->turnLeft(50, 50);
            }
//            cout << "preso pra parede" << endl;
        }

        // girar caso robo prenda a bola na parede - 8 cm
        if (robot.distanceFrom(state.ball.position) < (8)) {

            if (robot.position.y < (Config::fieldSize.y / 2)) {
                c = movimentation->turnLeft(60, 60);
            } else {
                c = movimentation->turnRight(60, 60);
            }
//            cout << "preso com bola" << endl;
        }
    }

    return c;
}

Command RobotStrategy::stopStrategy(Command c) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    float maxDistance = 12; // 12 cm
    float distanceTarget = robot.distanceFrom(target);

/* 	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}
*/

    if (distanceTarget < maxDistance) {
        c.left = c.left * (distanceTarget / maxDistance);
        c.right = c.right * (distanceTarget / maxDistance);
    }

    if (distanceTarget < 4) {

        if (robot.cosFrom(state.ball.projection) < -0.8 || robot.cosFrom(state.ball.projection) > 0.8) {
            c = movimentation->stop();

        } else {

            if (robot.sinFrom(state.ball.position) > 0) {
                c = movimentation->turnRight(10, 10);
            } else {
                c = movimentation->turnLeft(10, 10);
            }
        }
    }

    return c;
}

Command RobotStrategy::kickStrategy(Command c) {
    return c;
}

Command RobotStrategy::blockedStrategy(Command c) {
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
