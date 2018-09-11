//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>
RobotStrategyDefender::RobotStrategyDefender() = default;

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategyDefender::defineTargetAndArrivalOrientation() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    /*
     Se a bola estiver no ataque, posiciona o defensor na frente do gol adversario para receber cruzamento, podendo ser na lateral direita,esquerda ou no centro, dependendo da posição da bola.
     */
    if ((ballProjection.x < vss::MAX_COORDINATE_X / 3)) {
        if (robot.position.x < vss::MAX_COORDINATE_X * 0.6) {
            if (robot.position.x > 34 &&
                (state.ball.position.x < 30 || state.ball.position.y < 20 || state.ball.position.y > 110)) {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, 67, 0);
            } else {
                if (robot.position.y < vss::MAX_COORDINATE_Y / 2) {
                    if (ballProjection.y > state.ball.position.y) {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.15, 0);
                    } else {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.75, 0);
                    }
                } else {
                    if (ballProjection.y > state.ball.position.y) {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.15, 0);
                    } else {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.75, 0);
                    }
                }
            }

        }
    } else {
        target = vss::Pose(vss::MAX_COORDINATE_X / 2, vss::MAX_COORDINATE_Y / 2, 0); // se a bola não estiver no ataque, manda o defensor para o meio do campo.
    }
    //Se a bola estiver na defesa posicionar defensor na entrada da aréa na direção da bola
    if(ballProjection.x > vss::MAX_COORDINATE_X / 2)
    {
        target.x = vss::MAX_COORDINATE_X* 0.8;
        target.y=ballProjection.y;
    }

    /*
    // posiciona o robo na defesa para facilitar a troca de posicao com o goleiro
    if (ballProjection.x > vss::MAX_COORDINATE_X / 2)
    {
        if (ballProjection.y > vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.7, vss::MAX_COORDINATE_Y * 0.2, 0);
        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.7, vss::MAX_COORDINATE_Y * 0.8, 0);
        }
    }
    */

    //Orientação pro lado do gol
    arrivalOrientation.x = target.x - 10;
    arrivalOrientation.y = target.y;

    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target){
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)){
            obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
        }
    }
    UnivectorField univectorField(2, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);
}
