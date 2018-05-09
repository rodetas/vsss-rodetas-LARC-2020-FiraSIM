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
    if(robot.position.x < imageSize.x*0.4){
        if(robot.position.y > imageSize.y/2){
            if(ballProjection.y < state.ball.position.y){
                target = btVector3(imageSize.x*0.5, imageSize.y*0.2);
            } else {
                target = btVector3(imageSize.x*0.5, imageSize.y*0.8);
            }
        } else {
            if(ballProjection.y < state.ball.position.y){
                target = btVector3(imageSize.x*0.5, imageSize.y*0.2);
            } else {
                target = btVector3(imageSize.x*0.5, imageSize.y*0.8);
            }
        }

    }else{
        // se a bola esta no ataque posiciona o robo no meio do campo
        target = btVector3(imageSize.x/2, imageSize.y/2);
    }

    // posiciona o robo na defesa para facilitar a troca de posicao com o goleiro
    if(ballProjection.x > imageSize.x/2){
        if(ballProjection.y > imageSize.y/2){
            target = btVector3(imageSize.x*0.7, imageSize.y*0.2);
        } else {
            target = btVector3(imageSize.x*0.7, imageSize.y*0.8);
        }
    }

    return target;
}

