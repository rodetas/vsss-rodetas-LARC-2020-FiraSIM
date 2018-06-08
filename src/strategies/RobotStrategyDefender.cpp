//
// Created by manoel on 23/04/18.
//

#include <strategies/RobotStrategyDefender.h>

RobotStrategyDefender::RobotStrategyDefender() = default;

Command RobotStrategyDefender::specificStrategy(Command c) {
    c = stopStrategy(c);

    return c;
}

btVector3 RobotStrategyDefender::defineTarget() {

    btVector3 target;
    btVector3 ballProjection = state.ball.projection;

    // altera o ponto de destino dependendo do sentido da bola, evitando bater no outro robo
    if (robot.position.x < Config::fieldSize.x * 0.4) {
        if (robot.position.y > Config::fieldSize.y / 2) {
            if (ballProjection.y < state.ball.position.y) {
                target = btVector3(Config::fieldSize.x * 0.5, Config::fieldSize.y * 0.2);
            } else {
                target = btVector3(Config::fieldSize.x * 0.5, Config::fieldSize.y * 0.8);
            }
        } else {
            if (ballProjection.y < state.ball.position.y) {
                target = btVector3(Config::fieldSize.x * 0.5, Config::fieldSize.y * 0.2);
            } else {
                target = btVector3(Config::fieldSize.x * 0.5, Config::fieldSize.y * 0.8);
            }
        }

    } else {
        // se a bola esta no ataque posiciona o robo no meio do campo
        target = btVector3(Config::fieldSize.x / 2, Config::fieldSize.y / 2);
    }

    // posiciona o robo na defesa para facilitar a troca de posicao com o goleiro
    if (ballProjection.x > Config::fieldSize.x / 2) {
        if (ballProjection.y > Config::fieldSize.y / 2) {
            target = btVector3(Config::fieldSize.x * 0.7, Config::fieldSize.y * 0.2);
        } else {
            target = btVector3(Config::fieldSize.x * 0.7, Config::fieldSize.y * 0.8);
        }
    }

    return target;
}

float RobotStrategyDefender::applyUnivectorField(btVector3 target) {

    btVector3 arrivalOrientation = defineArrivalOrientation(target);

    vector<pair<btVector3, btVector3>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
            obstacles.push_back(make_pair(r.position, r.vectorSpeed));
        }
    }

    UnivectorField univectorField(2, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);
}

btVector3 RobotStrategyDefender::defineArrivalOrientation(btVector3 target) {
    btVector3 goal(0, 75);
    btVector3 arrivalOrientation;

    if((target.x == state.ball.projection.x) && (target.y == state.ball.projection.y)){

        float numerator = abs(target.y - goal.y);
        float denominator = abs(target.x - goal.x);
        float tg = (numerator/denominator);
        float deltaX = 10 * (1/sqrt(1 + (tg*tg)));
        float deltaY = tg * deltaX;

        if(target.y < goal.y){
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y + deltaY;
        }else{
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y - deltaY;
        }
        return arrivalOrientation;
    } else{
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y;
        return arrivalOrientation;
    }
}


