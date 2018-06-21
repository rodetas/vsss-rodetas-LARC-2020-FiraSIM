//
// Created by manoel on 16/04/18.
//

#include "Communication/StateReceiverAdapter.h"

StateReceiverAdapter::StateReceiverAdapter(vss::TeamType teamColor, vss::FieldTransformationType changeSide) {
    this->teamColor = teamColor;
    this->changeSide = changeSide;

    createSocketReceiveState();
}

void StateReceiverAdapter::createSocketReceiveState() {
    stateReceiver.createSocket();
}

RodetasState StateReceiverAdapter::receiveState() {

    // receives a vss::State from sdk or wait until a new packet comes
    vss::State state = stateReceiver.receiveState(changeSide);

    // converts vss::State to RodetasState
    RodetasState newState;
    newState.ball.setPosition(vss::Point(state.ball.x, state.ball.y));
    newState.ball.setLinearSpeed(Math::calculateLinearSpeed(state.ball.speedX, state.ball.speedY));
    newState.ball.setVectorSpeed(vss::Point(state.ball.speedX, state.ball.speedY));
    newState.ball.setProjection(Math::calculateProjection(vss::Point(state.ball.x, state.ball.y), state.ball.speedX, state.ball.speedY));

    // inserts team robots in the beginning of the vector and push opponents in the end
    if(teamColor == vss::TeamType::Yellow){

        for(auto vssRobot : state.teamYellow){
            RobotState robot;
            robot.setPosition(vss::Point(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(vss::Point(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            robot.setVectorSpeed(vss::Point(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }

        for(auto vssRobot : state.teamBlue){
            RobotState robot;
            robot.setPosition(vss::Point(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(vss::Point(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            robot.setVectorSpeed(vss::Point(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }

    } else {

        for(auto vssRobot : state.teamBlue){
            RobotState robot;
            robot.setPosition(vss::Point(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(vss::Point(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            robot.setVectorSpeed(vss::Point(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }

        for(auto vssRobot : state.teamYellow){
            RobotState robot;
            robot.setPosition(vss::Point(vssRobot.x, vssRobot.y));
            robot.setProjection(Math::calculateProjection(vss::Point(vssRobot.x, vssRobot.y), vssRobot.speedX, vssRobot.speedY));
            robot.setAngle(vssRobot.angle);
            robot.setAngularSpeed(vssRobot.speedAngle);
            robot.setLinearSpeed(Math::calculateLinearSpeed(vssRobot.speedX, vssRobot.speedY));
            robot.setVectorSpeed(vss::Point(vssRobot.speedX, vssRobot.speedY));
            newState.robots.emplace_back(robot);
        }
    }

    return newState;
}

