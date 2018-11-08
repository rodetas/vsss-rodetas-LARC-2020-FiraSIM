//
// Created by manoel on 23/04/18.
//

#include <Domain/Constants.h>
#include "Strategies/RobotStrategyGoal.h"

RobotStrategyGoal::RobotStrategyGoal(){
    mindSet = MindSet::GoalKeeperStrategy;

    stopGoalKeeper = true;
}

vss::WheelsCommand RobotStrategyGoal::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    if(stopGoalKeeper){
        c = stopStrategy(c);
    }

    return c;
}

vss::Pose RobotStrategyGoal::defineTarget() {
    vss::Pose goalTarget;
    vss::Point ballProjection = state.ball.projection;
    vss::Point ballPosition = state.ball.position;

    stopGoalKeeper = true;

    // posição para seguir linha da bola
    goalTarget.x = vss::MAX_COORDINATE_X - 20;
    goalTarget.y = ballProjection.y;

    // máximo que pode ir até a lateral da área
    if(state.ball.position.x > vss::MAX_COORDINATE_X*0.8){
        if (goalTarget.y > vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 3) {
            goalTarget.y = vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 3;

        } else if (goalTarget.y < vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 3) {
            goalTarget.y = vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 3;
        }
    } else {
        if (goalTarget.y > vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 4) {
            goalTarget.y = vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 4;

        } else if (goalTarget.y < vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 4) {
            goalTarget.y = vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 4;
        }
    }

    // ir na bola quando ela está dentro da area
    if (ballPosition.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 ) &&
        ballPosition.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2) &&
        ballPosition.x > vss::MAX_COORDINATE_X - 30) {

        // Testar esse target como sendo ballProjection ou ballPosition
        goalTarget.x = ballPosition.x;
        goalTarget.y = ballPosition.y;

        if (state.ball.vectorSpeed.x > 0) {
            // bola indo em direcao ao gol
            goalTarget.x = ballPosition.x;
            goalTarget.y = ballPosition.y;
        }

        stopGoalKeeper = false;
    }

    if (robot.position.y < goalTarget.y) {
        goalTarget.angle = M_PI/2 - M_PI/6;
    } else {
        goalTarget.angle = (3 * M_PI)/2 + M_PI/6;
    }

    return goalTarget;
}

float RobotStrategyGoal::applyUnivectorField(vss::Pose target) {
    /* Se o target for a bola e se a bola estiver atrás do goleiro indo pro gol, definir angulo de chegada
     * para que o robô chega até a bola por trás evitando gol contra e a levando para fora do gol*/

    UnivectorField univectorField;

    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    if ((target.x == state.ball.position.x) && (target.y == state.ball.position.y)) {
        if (target.y > vss::MAX_COORDINATE_Y / 2 - Config::goalSize.y/2 && target.y < vss::MAX_COORDINATE_Y/2 + Config::goalSize.y/2) {
            if (target.x > robot.position.x) {
                univectorField.setUnivectorWithCurves();
            }
        }
    }

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}

vss::WheelsCommand RobotStrategyGoal::stopStrategy(vss::WheelsCommand command) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    vss::WheelsCommand c = command;
    float maxDistance = (12); // 12 cm
    float distanceTarget = (float) robot.distanceFrom(target);

    if (distanceTarget < maxDistance) {
        c.leftVel = command.leftVel * (distanceTarget / maxDistance);
        c.rightVel = command.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < (4)) {

        if ((robot.angle > 70 && robot.angle < 110) || (robot.angle > 250 && robot.angle < 290)) {
            c = movimentation.stop();
        } else {
            if ((robot.angle > 0 and robot.angle < 90) or (robot.angle > 180 and robot.angle < 270)){
                c = movimentation.turnRight(25, 25);
            } else {
                c = movimentation.turnLeft(25, 25);
            }
        }
    }

    return c;
}
