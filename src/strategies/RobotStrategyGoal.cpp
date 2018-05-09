//
// Created by manoel on 23/04/18.
//

#include "strategies/RobotStrategyGoal.h"

RobotStrategyGoal::RobotStrategyGoal() = default;

Command RobotStrategyGoal::specificStrategy(Command c) {
    c = stop_strategy(c);

    return c;
}

btVector3 RobotStrategyGoal::defineTarget() {
    btVector3 goal_target = btVector3(0,0);
    btVector3 ball_projection = state.ball.projection;

    // posição para seguir linha da bola
    goal_target.x = Config::fieldSize.x - 20;
    goal_target.y = ball_projection.y;

    // máximo que pode ir até a lateral da área
    if(goal_target.y > Config::fieldSize.y/2 + goalAreaSize.y/2){
        goal_target.y = Config::fieldSize.y/2 + goalAreaSize.y/2;

    } else if(goal_target.y < Config::fieldSize.y/2 - goalAreaSize.y/2){
        goal_target.y = Config::fieldSize.y/2 - goalAreaSize.y/2;
    }

    // ir na bola quando ela está dentro da area
    if (ball_projection.y > (Config::fieldSize.y/2 - goalAreaSize.y/2) &&
        ball_projection.y < (Config::fieldSize.y/2 + goalAreaSize.y/2) &&
        ball_projection.x > Config::fieldSize.x - 30){

        goal_target = ball_projection;
    }

    // quando esta agarrado manda ir para o centro do gol na tentativa de soltar
    if(strategyBase.isStoppedFor(90) && robot.distanceFrom(goal_target) > 6){
        goal_target.x = Config::fieldSize.x - 10;
        goal_target.y = Config::fieldSize.y/2;
    }

    return goal_target;
}

