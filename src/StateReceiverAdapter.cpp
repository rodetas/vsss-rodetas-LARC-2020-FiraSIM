//
// Created by manoel on 16/04/18.
//

#include <RodetasRobot.h>
#include "StateReceiverAdapter.h"

StateReceiverAdapter::StateReceiverAdapter() {
    createSocketReceiveState();
}

void StateReceiverAdapter::createSocketReceiveState() {
    interfaceReceive.createSocketReceiveState();
}

RodetasState StateReceiverAdapter::receiveState(bool changeSide, TeamColor::Color mainColor) {

    // receives a vss::State from sdk or wait until a new packet comes
    vss::State state = interfaceReceive.receiveState((vss::FieldTransformation)changeSide);

    // converts vss::State to RodetasState
    RodetasState newState;
    newState.ball.setPosition(btVector3(state.ball.x, state.ball.y, 0));
    newState.ball.setLinearSpeed(Math::calculateLinearSpeed(state.ball.speedX, state.ball.speedY));
    newState.ball.setProjection(Math::calculateProjection(btVector3(state.ball.x, state.ball.y), state.ball.speedX, state.ball.speedY));

    // inserts team robots in the beginning of the vector and push opponents in the end
    if(mainColor == TeamColor::YELLOW){
        for(auto vssRobot : state.teamYellow){
            RobotState robot;
            robot.setPosition(btVector3(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(btVector3(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }

        for(auto vssRobot : state.teamBlue){
            RobotState robot;
            robot.setPosition(btVector3(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(btVector3(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }

    } else {

        for(auto vssRobot : state.teamBlue){
            RobotState robot;
            robot.setPosition(btVector3(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(btVector3(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }

        for(auto vssRobot : state.teamYellow){
            RobotState robot;
            robot.setPosition(btVector3(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(btVector3(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }
    }

    return newState;
}

