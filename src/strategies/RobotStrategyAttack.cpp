//
// Created by manoel on 18/04/18.
//

#include "strategies/RobotStrategyAttack.h"

RobotStrategyAttack::RobotStrategyAttack() {

}

Command RobotStrategyAttack::specificStrategy(Command c){
    c = kickStrategy(c);
    c = cornerStrategy(c);

    if (strategyBase.isParallelToGoal()){

        int halfGoal1 = Config::fieldSize.y/2 + (Config::goalSize.y/2);
        int halfGoal2 = Config::fieldSize.y/2 - (Config::goalSize.y/2);

        if ( robot.distanceFrom(state.ball.position) < 7 &&
             robot.position.x < Config::fieldSize.x*0.25 && robot.position.y > halfGoal2 && robot.position.y < halfGoal1){

            if (robot.position.y < state.ball.position.y) {
                c = movimentation->turnRight(80, 80);
            } else {
                c = movimentation->turnLeft(80, 80);
            }
        }
    }

    return c;
}

btVector3 RobotStrategyAttack::defineTarget() {

    btVector3 target = state.ball.position;
/*
    btVector3 centerGoal = btVector3(0, Config::fieldSize.y/2);
    double angleRobotGoal = Math::angulation(robot.position, centerGoal);

    if(angleRobotGoal < 45.0 && angleRobotGoal > -45.0 && (robot.cosFrom(centerGoal) < -0.8 || robot.cosFrom(centerGoal) > 0.8) &&
       (robot.cosFrom(state.ball.position) < -0.8 || robot.cosFrom(state.ball.getPosition()) > 0.8) &&
       robot.position.x > state.ball.position.x && robot.distanceFrom(state.ball.position) < (8)){

        target = centerGoal;
    }

    if(state.ball.projection.x > Config::fieldSize.x*0.3 && state.ball.projection.x > robot.position.x){
        if(state.ball.projection.y < Config::fieldSize.y/2){
            target.y = state.ball.projection.y + (8);
            target.x = state.ball.projection.x;
        } else {
            target.y = state.ball.projection.y - (8);
            target.x = state.ball.projection.x;
        }
    }

    int halfGoal1 = Config::fieldSize.y/2 + Config::goalSize.y * 0.85;
    int halfGoal2 = Config::fieldSize.y/2 - Config::goalSize.y * 0.85;

    if(((state.ball.projection.y < halfGoal1 && state.ball.projection.y > halfGoal2 && state.ball.projection.x > Config::fieldSize.x*0.80))){
        target = btVector3(Config::fieldSize.x/2, Config::fieldSize.y/2);
    }

    // verifies the limits of the destination
    if (target.y < 0) target.y = 0;
    if (target.y > Config::fieldSize.y) target.y = Config::fieldSize.y;
*/
    return target;
}
