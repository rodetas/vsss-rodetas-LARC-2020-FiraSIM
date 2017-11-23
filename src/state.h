#ifndef STATE_H_
#define STATE_H_

#include "common.h"
#include "robot.h"
#include "ball.h"

using namespace common;

class State {

public:
    Robot robots[6];
      
    Ball ball;

    btVector3 v_ball;

    //! Default constructor: State s;
    State(){};

    static State Global_State2State(vss_state::Global_State global_state, string main_color){
        State state;

        state.ball.pose.x = global_state.balls(0).pose().x();           // Pos X
        state.ball.pose.y = global_state.balls(0).pose().y();           // Pos Y

        state.ball.v_ball.x = global_state.balls(0).v_pose().x();         // Vel X
        state.ball.v_ball.y = global_state.balls(0).v_pose().y();         // Vel Y

//        state.ball_kalman.x = global_state.balls(0).k_pose().x();         // Kalman Pos X
//        state.ball_kalman.y = global_state.balls(0).k_pose().y();         // kalman Pos Y

//        state.v_ball_kalman.x = global_state.balls(0).k_v_pose().x();       // Kalman Vel X
//        state.v_ball_kalman.y = global_state.balls(0).k_v_pose().y();       // Kalman Vel Y


        if(main_color == "yellow"){
            for(int i = 0 ; i < 3 ; i++){
                // Yellow Robots POSE
                state.robots[i].pose.x =  global_state.robots_yellow(i).pose().x();           // Pos X
                state.robots[i].pose.y = global_state.robots_yellow(i).pose().y();           // Pos Y
                state.robots[i].pose.z =  global_state.robots_yellow(i).pose().yaw();         // Rotation in Z Axis (YAW)

                state.robots[i].pose.z = state.robots[i].pose.z * (180.0/M_PI);	// CONVERT TO DEGREES

                state.robots[i].pose.z -= 180; // 180 if comes from VSS-Simulator

                if(state.robots[i].pose.z < 0){
                    state.robots[i].pose.z += 360;
                }

                // Yellow Robots VELOCITIES
                state.robots[i].v_pose.x = global_state.robots_yellow(i).v_pose().x();         // Vel X
                state.robots[i].v_pose.y = global_state.robots_yellow(i).v_pose().y();         // Vel Y
                state.robots[i].v_pose.z = global_state.robots_yellow(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

                state.robots[i].v_pose.z = state.robots[i].v_pose.z * (180.0/M_PI);	// CONVERT TO DEGREES
                                                
                state.robots[i].v_pose.z -= 180; // 180 if comes from VSS-Simulator

                if(state.robots[i].v_pose.z < 0){
                    state.robots[i].v_pose.z += 360;
                }

/*
                // Yellow Robots Kalman predict POSE
                state.robots_kalman[i].pose.x = global_state.robots_yellow(i).k_pose().x();         // Kalman Pos X
                state.robots_kalman[i].pose.y = global_state.robots_yellow(i).k_pose().y();         // Kalman Pos Y
                state.robots_kalman[i].pose.z = global_state.robots_yellow(i).k_pose().yaw();       // Kalman Rotation in Z Axis (YAW)

                // Yellow Robots Kalman predict VELOCITYS
                state.robots_kalman[i].v_pose.x = global_state.robots_yellow(i).k_v_pose().x();       // Kalman Vel X
                state.robots_kalman[i].v_pose.y = global_state.robots_yellow(i).k_v_pose().y();       // Kalman Vel Y
                state.robots_kalman[i].v_pose.z = global_state.robots_yellow(i).k_v_pose().yaw();     // Kalman Vel Rotation in Z Axis (YAW)
*/

/*
                // Blue Robots POSE
                state.robots[i+3].pose.x =  global_state.robots_blue(i).pose().x();           // Pos X
                state.robots[i+3].pose.y = global_state.robots_blue(i).pose().y();           // Pos Y
                state.robots[i+3].pose.z =  global_state.robots_blue(i).pose().yaw();         // Rotation in Z Axis (YAW)

                // Blue Robots VELOCITYS
                state.robots[i+3].v_pose.x = global_state.robots_blue(i).v_pose().x();         // Vel X
                state.robots[i+3].v_pose.y = global_state.robots_blue(i).v_pose().y();         // Vel Y
                state.robots[i+3].v_pose.z = global_state.robots_blue(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

                // Blue Robots Kalman predict POSE
                state.robots_kalman[i+3].pose.x = global_state.robots_blue(i).k_pose().x();         // Kalman Pos X
                state.robots_kalman[i+3].pose.y = global_state.robots_blue(i).k_pose().y();         // Kalman Pos Y
                state.robots_kalman[i+3].pose.z = global_state.robots_blue(i).k_pose().yaw();       // Kalman Rotation in Z Axis (YAW)

                // Blue Robots Kalman predict VELOCITYS
                state.robots_kalman[i+3].v_pose.x = global_state.robots_blue(i).k_v_pose().x();       // Kalman Vel X
                state.robots_kalman[i+3].v_pose.y = global_state.robots_blue(i).k_v_pose().y();       // Kalman Vel Y
                state.robots_kalman[i+3].v_pose.z = global_state.robots_blue(i).k_v_pose().yaw();     // Kalman Vel Rotation in Z Axis (YAW)
*/                
            }
        }else{
            for(int i = 0 ; i < 3 ; i++){
                // Yellow Robots POSE
                state.robots[i].pose.x =  global_state.robots_blue(i).pose().x();           // Pos X
                state.robots[i].pose.y = global_state.robots_blue(i).pose().y();           // Pos Y
                state.robots[i].pose.z =  global_state.robots_blue(i).pose().yaw();         // Rotation in Z Axis (YAW)

                state.robots[i].pose.z = state.robots[i].pose.z * (180.0/M_PI);	// CONVERT TO DEGREES

                state.robots[i].pose.z -= 180; // 180 if comes from VSS-Simulator

                if(state.robots[i].pose.z < 0){
                    state.robots[i].pose.z += 360;
                }

                // Yellow Robots VELOCITYS
                state.robots[i].v_pose.x = global_state.robots_blue(i).v_pose().x();         // Vel X
                state.robots[i].v_pose.y = global_state.robots_blue(i).v_pose().y();         // Vel Y
                state.robots[i].v_pose.z = global_state.robots_blue(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

                state.robots[i].v_pose.z = state.robots[i].v_pose.z * (180.0/M_PI);	// CONVERT TO DEGREES
                                                
                state.robots[i].v_pose.z -= 180; // 180 if comes from VSS-Simulator

                if(state.robots[i].v_pose.z < 0){
                    state.robots[i].v_pose.z += 360;
                }

/*
                // Yellow Robots Kalman predict POSE
                state.robots_kalman[i].pose.x = global_state.robots_blue(i).k_pose().x();         // Kalman Pos X
                state.robots_kalman[i].pose.y = global_state.robots_blue(i).k_pose().y();         // Kalman Pos Y
                state.robots_kalman[i].pose.z = global_state.robots_blue(i).k_pose().yaw();       // Kalman Rotation in Z Axis (YAW)

                // Yellow Robots Kalman predict VELOCITYS
                state.robots_kalman[i].v_pose.x = global_state.robots_blue(i).k_v_pose().x();       // Kalman Vel X
                state.robots_kalman[i].v_pose.y = global_state.robots_blue(i).k_v_pose().y();       // Kalman Vel Y
                state.robots_kalman[i].v_pose.z = global_state.robots_blue(i).k_v_pose().yaw();     // Kalman Vel Rotation in Z Axis (YAW)
*/

/*
                // Blue Robots POSE
                state.robots[i+3].pose.x =  global_state.robots_yellow(i).pose().x();           // Pos X
                state.robots[i+3].pose.y = global_state.robots_yellow(i).pose().y();           // Pos Y
                state.robots[i+3].pose.z =  global_state.robots_yellow(i).pose().yaw();         // Rotation in Z Axis (YAW)

                // Blue Robots VELOCITYS
                state.robots[i+3].v_pose.x = global_state.robots_yellow(i).v_pose().x();         // Vel X
                state.robots[i+3].v_pose.y = global_state.robots_yellow(i).v_pose().y();         // Vel Y
                state.robots[i+3].v_pose.z = global_state.robots_yellow(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

                // Blue Robots Kalman predict POSE
                state.robots_kalman[i+3].pose.x = global_state.robots_yellow(i).k_pose().x();         // Kalman Pos X
                state.robots_kalman[i+3].pose.y = global_state.robots_yellow(i).k_pose().y();         // Kalman Pos Y
                state.robots_kalman[i+3].pose.z = global_state.robots_yellow(i).k_pose().yaw();       // Kalman Rotation in Z Axis (YAW)

                // Blue Robots Kalman predict VELOCITYS
                state.robots_kalman[i+3].v_pose.x = global_state.robots_yellow(i).k_v_pose().x();       // Kalman Vel X
                state.robots_kalman[i+3].v_pose.y = global_state.robots_yellow(i).k_v_pose().y();       // Kalman Vel Y
                state.robots_kalman[i+3].v_pose.z = global_state.robots_yellow(i).k_v_pose().yaw();     // Kalman Vel Rotation in Z Axis (YAW)
*/
            }
        }

        return state;
    }

    void show(){
        /* cout << endl << endl << "Robots Team 1:" << endl;
        for(int i = 0 ; i < 3 ; i++){
            robots[i].show();
        }
        cout << endl << endl << "Robots Team 2:" << endl;
        for(int i = 3 ; i < 6 ; i++){
            robots[i].show();
        }

        cout << endl << endl << "Ball:" << endl;
        ball.show();
        ball_kalman.show(); */
    }

};

#endif