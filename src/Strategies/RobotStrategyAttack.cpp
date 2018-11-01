//
// Created by manoel on 18/04/18.
//

#include "Strategies/RobotStrategyAttack.h"

RobotStrategyAttack::RobotStrategyAttack() {
    stopAttacker = false;
}

vss::WheelsCommand RobotStrategyAttack::specificStrategy(vss::WheelsCommand c) {
    c = kickStrategy(c);
    c = cornerStrategy(c);

    if (stopAttacker) {
        c = stopStrategy(c);
    }

    if (strategyBase.isParallelToGoal()) {

        int halfGoal1 = vss::MAX_COORDINATE_Y / 2 + (Config::goalSize.y / 2);
        int halfGoal2 = vss::MAX_COORDINATE_Y / 2 - (Config::goalSize.y / 2);

        if (robot.distanceFrom(state.ball.position) < 7 &&
            robot.position.x < vss::MAX_COORDINATE_X * 0.25 && robot.position.y > halfGoal2 &&
            robot.position.y < halfGoal1) {

            if (robot.position.y < state.ball.position.y) {
                c = movimentation.turnRight(80, 80);
            } else {
                c = movimentation.turnLeft(80, 80);
            }
        }
    }

    return c;
}

vss::Pose RobotStrategyAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);

    //Posiciona o atacante no meio do campo para ele nao interferir na defesa
    if (state.ball.projection.x > vss::MAX_COORDINATE_X * 0.6) {
        if (state.ball.projection.y < vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.55, vss::MAX_COORDINATE_Y * 0.8, 0);
            stopAttacker = true;
        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.55, vss::MAX_COORDINATE_Y * 0.2, 0);
            stopAttacker = true;
        }
    } else {
        stopAttacker = false;

        target.x = state.ball.position.x;
        target.y = state.ball.position.y;

        target.angle = Math::arrivalAngle(target, centerGoal);

        //Angulos para quando robô estiver na parede
        if (target.y < vss::MAX_COORDINATE_Y * 0.1) {
            target.angle = 0;
        }
        if (target.y > vss::MAX_COORDINATE_Y * 0.88) {
            target.angle = 0;
        }

    }

    return target;
}

float RobotStrategyAttack::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    //Se o target for a bola ou sua projeção e o robo estiver longe, desvia de todos
    if ((target.x == state.ball.position.x && target.y == state.ball.position.y) ||
        (target.x == state.ball.projection.x && target.y == state.ball.position.y)) {
        if (robot.distanceFrom(target) > 15) {
            //Obstáculos roboôs
            for (auto &r: state.robots) {
                if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                    obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
                }
            }
        }
    }

    UnivectorField univectorField;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}
