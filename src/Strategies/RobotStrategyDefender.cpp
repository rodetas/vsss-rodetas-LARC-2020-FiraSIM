//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>
RobotStrategyDefender::RobotStrategyDefender() = default;

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategyDefender::positionDefenderInAttack() {
    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    // verifica se a projeção da bola está no campo adversário
    if ((ballProjection.x < vss::MAX_COORDINATE_X / 3)) {
        //verifica se o defensor está no campo de ataque
        if (robot.position.x < vss::MAX_COORDINATE_X * 0.6) {
            /*verifica se o robô está fora da área adversária && se a bola está dentro da área inimiga */
            if (robot.position.x > 34 &&
                (state.ball.position.x < 30 || state.ball.position.y < 20 || state.ball.position.y > 110)) {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, 67, 0);
            } else {
                /*se a bola não estiver na posição de chute, ou seja dentro da área, então posiciona o robô
                 * no canto direito, esquerdo ou no meio, dependendo da orientação da bola
                 * */
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
        // se a bola não estiver no ataque posiciona o defensor no meio do campo.
        target = vss::Pose(vss::MAX_COORDINATE_X / 2, vss::MAX_COORDINATE_Y / 2, 0);
    }

    return target;
}

vss::Pose RobotStrategyDefender::defineTargetAndArrivalOrientation() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    /* Posicionamento para receber cruzamento
     * se a bola estiver no ataque, posiciona defensor perto da área adversária*/
    target = positionDefenderInAttack();

    /* Segunda linha de defesa
     * verifica se a projeção da bola está em seu campo */
    if(ballProjection.x > vss::MAX_COORDINATE_X / 2) {
        // posiciona defensor na frente da aréa
        target.x = vss::MAX_COORDINATE_X* 0.8;
        // posiciona defensor na direção da projeção da bola
        target.y=ballProjection.y;
    }

    //Orientação pro lado do gol
    target.angle = 0;

    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target){
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
