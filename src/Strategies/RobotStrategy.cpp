//
// Created by manoel on 17/04/18.
//

#include <RobotStrategy.h>

RobotStrategy::RobotStrategy() = default;

vss::WheelsCommand RobotStrategy::applyStrategy(RobotState r, RodetasState s, RobotStrategyBase base) {
    this->robot = r;
    this->state = s;
    this->strategyBase = base;

    // defines robot's target,
    target = this->defineTarget();

    fi = this->applyUnivectorField(target);

    // defines robot's pwm
    command = movimentation.movePlayers(robot, fi, target, RobotSpeed ::NORMAL, this->mindSet);

    // defines specific strategy such as corner strategy or kick strategy - can be applied or not
    command = this->specificStrategy(command);

    return command;
}

vss::WheelsCommand RobotStrategy::cornerStrategy(vss::WheelsCommand c) {

    if (strategyBase.isBoard() && strategyBase.isStopped()) {

        // girar caso robo esteja preso de frente pra parede
        if ((cos(fi - Math::toRadian(robot.angle)) > -0.9) && (cos(fi - Math::toRadian(robot.angle)) < 0.9)){

            if (sin(fi - Math::toRadian(robot.angle)) > 0) {
                c = movimentation.turnRight(30, 30);
            } else {
                c = movimentation.turnLeft(30, 30);
            }

        }

        // girar caso robo prenda a bola na parede - 8 cm
        if (robot.distanceFrom(state.ball.position) < (8)) {
            if (robot.position.y < (vss::MAX_COORDINATE_Y / 2)) {
                c = movimentation.turnLeft(80, 80);
            } else {
                c = movimentation.turnRight(80, 80);
            }

        }
    }

    return c;
}

vss::WheelsCommand RobotStrategy::stopStrategy(vss::WheelsCommand c) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    float maxDistance = 12; // 12 cm
    float distanceTarget = robot.distanceFrom(target);

/* 	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}
*/

    if (distanceTarget < maxDistance) {
        c.leftVel = c.leftVel * (distanceTarget / maxDistance);
        c.rightVel = c.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < 4) {

        if (robot.cosFrom(state.ball.projection) < -0.8 || robot.cosFrom(state.ball.projection) > 0.8) {
            c = movimentation.stop();

        } else {

            if (robot.sinFrom(state.ball.position) > 0) {
                c = movimentation.turnRight(10, 10);
            } else {
                c = movimentation.turnLeft(10, 10);
            }
        }
    }

    return c;
}

vss::WheelsCommand RobotStrategy::kickStrategy(vss::WheelsCommand c) {
    return c;
}

vss::WheelsCommand RobotStrategy::blockedStrategy(vss::WheelsCommand c) {
    return c;
}

