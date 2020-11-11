//
// Created by manoel on 16/04/18.
//

#include "Communication/StateReceiverAdapter.h"

StateReceiverAdapter::StateReceiverAdapter(vss::TeamType teamColor, vss::FieldTransformationType changeSide) {
    this->teamColor = teamColor;
    this->changeSide = changeSide;

    //createSocketReceiveState();
}

void StateReceiverAdapter::createSocketReceiveState() {
    //stateReceiver.createSocket();
}

RodetasState StateReceiverAdapter::receiveState(fira_message::sim_to_ref::Environment packet) {
    
            //printf("-----Received Wrapper Packet---------------------------------------------\n");
            //see if the packet contains a robot detection frame:
                fira_message::Frame detection = packet.frame();

                int robots_blue_n =  detection.robots_blue_size();
                int robots_yellow_n =  detection.robots_yellow_size();

                //BALL STATE
                fira_message::Ball ball = detection.ball();
                // converts vss::State to RodetasState
                RodetasState newState;
                

    // inserts team robots in the beginning of the vector and push opponents in the end
    if(teamColor == vss::TeamType::Yellow){

                newState.ball.setPosition(Math::conversionYellow(vss::Point(ball.x(), ball.y())));
                newState.ball.setLinearSpeed(Math::calculateLinearSpeed(ball.vx()*100, ball.vy()*(-1)*100));
                newState.ball.setVectorSpeed(vss::Point(ball.vx()*100, ball.vy()*(-1)*100));
                newState.ball.setProjection(Math::calculateProjection(Math::conversionYellow(vss::Point(ball.x(), ball.y())), ball.vx()*100, ball.vy()*(-1)*100));
                //std::cout << "BOLA(X,Y): "<<(Math::conversionYellow(vss::Point(ball.x(), ball.y()))).x<<" / "<<(Math::conversionYellow(vss::Point(ball.x(), ball.y()))).y<<std::endl;
        for(int i = 0; i < robots_yellow_n; i++){
            fira_message::Robot firaRobot = detection.robots_yellow(i);
            RobotState robot;  
            robot.setPosition(Math::conversionYellow(vss::Point(firaRobot.x(), firaRobot.y())));
            robot.setProjection(Math::calculateProjection(Math::conversionYellow(vss::Point(firaRobot.x(), firaRobot.y())), firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setAngle(Math::toDegree(firaRobot.orientation()*(-1)));
            robot.setAngularSpeed(0);
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setVectorSpeed(vss::Point(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            newState.robots.emplace_back(robot);
        
        }

        for(int i = 0; i < robots_blue_n; i++){
            fira_message::Robot firaRobot = detection.robots_blue(i);
            RobotState robot;
            robot.setPosition(Math::conversionYellow(vss::Point(firaRobot.x(), firaRobot.y())));
            robot.setProjection(Math::calculateProjection(Math::conversionYellow(vss::Point(firaRobot.x(), firaRobot.y())), firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setAngle(Math::toDegree(firaRobot.orientation()*(-1)));
            robot.setAngularSpeed(0);
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setVectorSpeed(vss::Point(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            newState.robots.emplace_back(robot);
        }

    } else {
                newState.ball.setPosition(Math::conversionBlue(vss::Point(ball.x(), ball.y())));
                newState.ball.setLinearSpeed(Math::calculateLinearSpeed(ball.vx()*100*(-1), ball.vy()*100));
                newState.ball.setVectorSpeed(vss::Point(ball.vx()*100*(-1), ball.vy()*100));
                newState.ball.setProjection(Math::calculateProjection(Math::conversionBlue(vss::Point(ball.x(), ball.y())), ball.vx()*100*(-1), ball.vy()*100));

       for(int i = 0; i < robots_blue_n; i++){
            fira_message::Robot firaRobot = detection.robots_blue(i);
           RobotState robot;
            robot.setPosition(Math::conversionBlue(vss::Point(firaRobot.x(), firaRobot.y())));
            robot.setProjection(Math::calculateProjection(Math::conversionBlue(vss::Point(firaRobot.x(), firaRobot.y())), firaRobot.vx()*(-1)*100, firaRobot.vy()*100));
            robot.setAngle(180-Math::toDegree(firaRobot.orientation()));
            robot.setAngularSpeed(0);
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx()*(-1)*100, firaRobot.vy()*100));
            robot.setVectorSpeed(vss::Point(firaRobot.vx()*(-1)*100, firaRobot.vy()*100));
            newState.robots.emplace_back(robot);
        }

        for(int i = 0; i < robots_yellow_n; i++){
            fira_message::Robot firaRobot = detection.robots_yellow(i);
            RobotState robot;
            robot.setPosition(Math::conversionBlue(vss::Point(firaRobot.x(), firaRobot.y())));
            robot.setProjection(Math::calculateProjection(Math::conversionBlue(vss::Point(firaRobot.x(), firaRobot.y())), firaRobot.vx()*(-1)*100, firaRobot.vy()*100));
            robot.setAngle(180-Math::toDegree(firaRobot.orientation()));
            robot.setAngularSpeed(0);
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx()*(-1)*100, firaRobot.vy()*100));
            robot.setVectorSpeed(vss::Point(firaRobot.vx()*(-1)*100, firaRobot.vy()*100));
            newState.robots.emplace_back(robot);
        }
    }

                

    // receives a vss::State from sdk or wait until a new packet comes
    //vss::State state = stateReceiver.receiveState(changeSide);

    

    return newState;
}

