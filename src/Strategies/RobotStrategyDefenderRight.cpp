//
// Created by leonardo on 19/09/18.
//

#include <iostream>
using namespace std;
#include <Strategies/RobotStrategyDefenderRight.h>
RobotStrategyDefenderRight::RobotStrategyDefenderRight() = default;

vss::WheelsCommand RobotStrategyDefenderRight::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategyDefenderRight::defineTargetAndArrivalOrientation() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    /* Linha de defesa lado esquerdo*/

    // posiciona defensor na frente da aréa
    target.x = vss::MAX_COORDINATE_X * 0.75;
    // se a bola estiver na parede, evita que o defensor fique preso na parede
    if(ballProjection.y >= (vss::MAX_COORDINATE_Y-5)){
        target.y = ballProjection.y-6;
    }
    // posiciona defensor na direção da projeção da bola no canto direito ou posiciona no meio do campo em y
    else if(ballProjection.y > vss::MAX_COORDINATE_Y/2) {
        target.y = ballProjection.y;
    }
    else {
        target.y = vss::MAX_COORDINATE_Y / 2 + 5;
    }

    //Orientação pro lado do gol
    target.angle = 0;

    return target;
}

float RobotStrategyDefenderRight::applyUnivectorField(vss::Pose target){
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)){
            obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
        }
    }
    UnivectorField univectorField;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}
