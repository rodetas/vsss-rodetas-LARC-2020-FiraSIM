//
// Created by leonardo on 19/09/18.
//

#include <iostream>
using namespace std;
#include <Strategies/RobotStrategyDefenderLeft.h>
RobotStrategyDefenderLeft::RobotStrategyDefenderLeft() = default;

vss::WheelsCommand RobotStrategyDefenderLeft::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);
    if(robot.distanceFrom(state.ball.position) < (12)){
        c = movimentation.turnLeft(80, 80);
    }
    return c;
}

vss::Pose RobotStrategyDefenderLeft::defineTargetAndArrivalOrientation() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;
    target.x = vss::MAX_COORDINATE_X * 0.75;
    //Se a bola passar pela linha de defesa, posiciona robo no canto do gol em x
    cout<<"posx"<<robot.position.x<<endl;
    cout<<"posy"<<robot.position.y<<endl;
    if(state.ball.position.x > vss::MAX_COORDINATE_X * 0.75){
        target.x = 150;
        target.y = 22;
        vss::Point(150, 22);
    }
    else {
        // Linha de defesa lado esquerdo
        // posiciona defensor na frente da aréa
        target.x = vss::MAX_COORDINATE_X * 0.75;
        // se a bola estiver na parede, evita que o defensor fique preso na parede
        if (ballProjection.y <= 5) {
            target.y = ballProjection.y + 5;
        }
            // posiciona defensor na direção da projeção da bola no canto esquerdo ou posiciona no meio do campo em y
        else if (ballProjection.y < vss::MAX_COORDINATE_Y / 2) {
            target.y = ballProjection.y;
        } else {
            target.y = vss::MAX_COORDINATE_Y / 2 - 7;
        }
    }

    cout<<"ballPosX"<<state.ball.position.x<<endl;
    cout<<"ballPosY"<<state.ball.position.y<<endl;
    //cout<<"robotPos"<<robot.position.x<<endl;
    //Orientação pro lado do gol
    target.angle = 0;

    return target;
}

float RobotStrategyDefenderLeft::applyUnivectorField(vss::Pose target){
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)){
            obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
        }
    }
    UnivectorField univectorField;
    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}