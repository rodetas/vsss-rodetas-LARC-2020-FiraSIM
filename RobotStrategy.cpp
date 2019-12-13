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

    float fi = this->applyUnivectorField(target);

    // defines robot's pwm
    command = movimentation.movePlayers(robot, fi);

    // defines specific strategy such as corner strategy or kick strategy - can be applied or not
    command = this->specificStrategy(command);

    return command;
}

//
vss::WheelsCommand RobotStrategy::cornerStrategy(vss::WheelsCommand c) {

    if (strategyBase.isBoard() && strategyBase.isStopped()) {

        // girar caso robo esteja preso de frente pra parede
        if (robot.cosFrom(state.ball.position) > -0.9 && robot.cosFrom(state.ball.position) < 0.9) {

            //robot.setAngle(75);

            if (robot.sinFrom(state.ball.position) > 0) {
                // c = movimentation.turnRight(50, 50);
                c = movimentation.stop();
                strategyBase.isBlocked(); // Giradinha para ganhar espaço e armar a jogada
                // Entao ...
                c = movimentation.turnRight(75, 35);
            } else {
                // c = movimentation.turnLeft(50, 50);
                c = movimentation.stop();
                strategyBase.isBlocked();
                // Entao ...
                c = movimentation.turnLeft(75, 35);
            }
//            cout << "preso pra parede" << endl;
        }

        // girar caso robo prenda a bola na parede - 8 cm
        if (robot.distanceFrom(state.ball.position) < (15)) {
            if (robot.position.y < (vss::MAX_COORDINATE_Y / 2)) {
                c = movimentation.stop();
                strategyBase.isBlocked(); // Giradinha para ganhar espaço e armar a jogada
                // Entao ...
                c = movimentation.turnLeft(60, 60);
            } else {
                c = movimentation.stop();
                strategyBase.isBlocked();
                // Entao ...
                c = movimentation.turnRight(60, 60);
            }
//            cout << "preso com bola" << endl;
        }
    }

    return c;
}

//
vss::WheelsCommand RobotStrategy::stopStrategy(vss::WheelsCommand c) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    float maxDistance = 12; // 12 cm
    float distanceTarget = robot.distanceFrom(target);

    /*REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}*/


    if (distanceTarget < maxDistance) {
        c.leftVel = c.leftVel * (distanceTarget / maxDistance);
        c.rightVel = c.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < 4) {

        if (robot.cosFrom(state.ball.projection) < -0.8 || robot.cosFrom(state.ball.projection) > 0.8) {
            c = movimentation.stop();

        } else {

            if (robot.sinFrom(state.ball.position) > 0) {
                // c = movimentation.turnRight(10, 10); <- Anterior
                c = movimentation.turnRight(10, 10);
            } else {
                // c = movimentation.turnLeft(10, 10); <- Anterior
                c = movimentation.turnLeft(10, 10);
            }
        }
    }

    return c;
}

/* Descobrir oque esse kickStrategy esta fazendo! */

vss::WheelsCommand RobotStrategy::kickStrategy(vss::WheelsCommand c) {

    /* Essa parte eu fiz apenas para ver como os robos iriam reagir*/

    float distanceTarget = robot.distanceFrom(target);

    if (distanceTarget < 4) {
        
        if (robot.sinFrom(state.ball.position) > 0) {
            c = movimentation.turnLeft(60, 60);
        } else {
            c = movimentation.turnRight(60, 60);
        }
    }

    return c;
}

vss::WheelsCommand RobotStrategy::blockedStrategy(vss::WheelsCommand c) {

    /* A ideia aqui era fazer os robos sairem mais rapido de uma marcacao */

    if (strategyBase.isBlocked() && strategyBase.isStopped()) {

        c = movimentation.turnRight(180, 180);

        if (strategyBase.isBlocked() && strategyBase.isStopped()) {

            c = movimentation.turnLeft(270, 270);

        }

    }

    return c;
}

