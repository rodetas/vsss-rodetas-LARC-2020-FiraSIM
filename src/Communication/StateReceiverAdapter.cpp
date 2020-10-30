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

RodetasState StateReceiverAdapter::receiveState(fira_message::sim_to_ref::Environment packet) {
    
            printf("-----Received Wrapper Packet---------------------------------------------\n");
            //see if the packet contains a robot detection frame:
                fira_message::Frame detection = packet.frame();


                int robots_blue_n =  detection.robots_blue_size();
                int robots_yellow_n =  detection.robots_yellow_size();

                //BALL STATE
                fira_message::Ball ball = detection.ball();
                // converts vss::State to RodetasState
                RodetasState newState;
                newState.ball.setPosition(vss::Point(ball.x(), ball.y()));
                newState.ball.setLinearSpeed(Math::calculateLinearSpeed(ball.vx(), ball.vy()));
                newState.ball.setVectorSpeed(vss::Point(ball.vx(), ball.vy()));
                newState.ball.setProjection(Math::calculateProjection(vss::Point(ball.x(), ball.y()), ball.vx(), ball.vy()));

    // inserts team robots in the beginning of the vector and push opponents in the end
    if(teamColor == vss::TeamType::Yellow){

        for(int i = 0; i < robots_yellow_n; i++){
            fira_message::Robot firaRobot = detection.robots_yellow(i);
            RobotState robot;
            robot.setPosition(vss::Point(firaRobot.x(), firaRobot.y()));
            robot.setProjection(Math::calculateProjection(vss::Point(firaRobot.x(), firaRobot.y()), firaRobot.vx(), firaRobot.vy()));
            robot.setAngle(firaRobot.orientation());
            robot.setAngularSpeed(firaRobot.orientation());
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx(), firaRobot.vy()));
            robot.setVectorSpeed(vss::Point(firaRobot.vx(), firaRobot.vy()));
            newState.robots.emplace_back(robot);
        }

        for(int i = 0; i < robots_blue_n; i++){
            fira_message::Robot firaRobot = detection.robots_blue(i);
            RobotState robot;
            robot.setPosition(vss::Point(firaRobot.x(), firaRobot.y()));
            robot.setProjection(Math::calculateProjection(vss::Point(firaRobot.x(), firaRobot.y()), firaRobot.vx(), firaRobot.vy()));
            robot.setAngle(firaRobot.orientation());
            robot.setAngularSpeed(firaRobot.orientation());
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx(), firaRobot.vy()));
            robot.setVectorSpeed(vss::Point(firaRobot.vx(), firaRobot.vy()));
            newState.robots.emplace_back(robot);
        }

    } else {

       for(int i = 0; i < robots_blue_n; i++){
            fira_message::Robot firaRobot = detection.robots_blue(i);
            RobotState robot;
            robot.setPosition(vss::Point(firaRobot.x(), firaRobot.y()));
            robot.setProjection(Math::calculateProjection(vss::Point(firaRobot.x(), firaRobot.y()), firaRobot.vx(), firaRobot.vy()));
            robot.setAngle(firaRobot.orientation());
            robot.setAngularSpeed(firaRobot.orientation());
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx(), firaRobot.vy()));
            robot.setVectorSpeed(vss::Point(firaRobot.vx(), firaRobot.vy()));
            newState.robots.emplace_back(robot);
        }

        for(int i = 0; i < robots_yellow_n; i++){
            fira_message::Robot firaRobot = detection.robots_yellow(i);
            RobotState robot;
            robot.setPosition(vss::Point(firaRobot.x(), firaRobot.y()));
            robot.setProjection(Math::calculateProjection(vss::Point(firaRobot.x(), firaRobot.y()), firaRobot.vx(), firaRobot.vy()));
            robot.setAngle(firaRobot.orientation());
            robot.setAngularSpeed(firaRobot.orientation());
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx(), firaRobot.vy()));
            robot.setVectorSpeed(vss::Point(firaRobot.vx(), firaRobot.vy()));
            newState.robots.emplace_back(robot);
        }
    }

                

    // receives a vss::State from sdk or wait until a new packet comes
    //vss::State state = stateReceiver.receiveState(changeSide);

    

    return newState;
}

