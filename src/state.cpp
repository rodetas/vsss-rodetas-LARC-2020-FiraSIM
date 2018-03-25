#include "state.h"

void State::show(){
    cout << endl << endl << "Robots Team 1:" << endl;
    for(int i = 0 ; i < 3 ; i++){
        cout << robots[i].show() << endl;
    }
    cout << endl << endl << "Robots Team 2:" << endl;
    for(int i = 3 ; i < 6 ; i++){
        cout << robots[i].show() << endl;
    }

    cout << endl << endl << "Ball:" << endl;
    cout << ball.show() << endl;
}

State State::Global_State2State(vss_state::Global_State global_state, string main_color){
    State state;

    btVector3 pose;
    btVector3 v_pose;

    pose.x = global_state.balls(0).pose().x();           // Pos X
    pose.y = global_state.balls(0).pose().y();           // Pos Y

    v_pose.x = global_state.balls(0).v_pose().x();         // Vel X
    v_pose.y = global_state.balls(0).v_pose().y();         // Vel Y

    state.ball.set_position(pose);
    state.ball.set_velocity_vector(v_pose);

//        state.ball_kalman.x = global_state.balls(0).k_pose().x();         // Kalman Pos X
//        state.ball_kalman.y = global_state.balls(0).k_pose().y();         // kalman Pos Y

//        state.v_ball_kalman.x = global_state.balls(0).k_v_pose().x();       // Kalman Vel X
//        state.v_ball_kalman.y = global_state.balls(0).k_v_pose().y();       // Kalman Vel Y


    if(main_color == "yellow"){
        for(int i = 0 ; i < 3 ; i++){
            // Yellow Robots POSE
            pose.x =  global_state.robots_yellow(i).pose().x();           // Pos X
            pose.y = global_state.robots_yellow(i).pose().y();           // Pos Y
            pose.z =  global_state.robots_yellow(i).pose().yaw();         // Rotation in Z Axis (YAW)

            pose.z = pose.z * (180.0/M_PI);	// CONVERT TO DEGREES

            pose.z -= 180; // 180 if comes from VSS-Simulator

            if(pose.z < 0){
                pose.z += 360;
            }

            // Yellow Robots VELOCITIES
            v_pose.x = global_state.robots_yellow(i).v_pose().x();         // Vel X
            v_pose.y = global_state.robots_yellow(i).v_pose().y();         // Vel Y
            v_pose.z = global_state.robots_yellow(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

            v_pose.z = v_pose.z * (180.0/M_PI);	// CONVERT TO DEGREES

            v_pose.z -= 180; // 180 if comes from VSS-Simulator

            if(v_pose.z < 0){
                v_pose.z += 360;
            }

            state.robots[i].set_position(pose);
            state.robots[i].set_velocity_vector(v_pose);

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


            // Blue Robots POSE
            pose.x =  global_state.robots_blue(i).pose().x();           // Pos X
            pose.y = global_state.robots_blue(i).pose().y();           // Pos Y
            pose.z =  global_state.robots_blue(i).pose().yaw();         // Rotation in Z Axis (YAW)

            // Blue Robots VELOCITYS
            v_pose.x = global_state.robots_blue(i).v_pose().x();         // Vel X
            v_pose.y = global_state.robots_blue(i).v_pose().y();         // Vel Y
            v_pose.z = global_state.robots_blue(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

            state.robots[i+3].set_position(pose);
            state.robots[i+3].set_velocity_vector(v_pose);
/*
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
            // blue Robots POSE
            pose.x =  global_state.robots_blue(i).pose().x();           // Pos X
            pose.y = global_state.robots_blue(i).pose().y();           // Pos Y
            pose.z =  global_state.robots_blue(i).pose().yaw();         // Rotation in Z Axis (YAW)

            pose.z = pose.z * (180.0/M_PI);	// CONVERT TO DEGREES

            pose.z -= 180; // 180 if comes from VSS-Simulator

            if(pose.z < 0){
                pose.z += 360;
            }

            // blue Robots VELOCITYS
            v_pose.x = global_state.robots_blue(i).v_pose().x();         // Vel X
            v_pose.y = global_state.robots_blue(i).v_pose().y();         // Vel Y
            v_pose.z = global_state.robots_blue(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

            v_pose.z = v_pose.z * (180.0/M_PI);	// CONVERT TO DEGREES

            v_pose.z -= 180; // 180 if comes from VSS-Simulator

            if(v_pose.z < 0){
                v_pose.z += 360;
            }

            state.robots[i].set_position(pose);
            state.robots[i].set_velocity_vector(v_pose);

/*
            // blue Robots Kalman predict POSE
            state.robots_kalman[i].pose.x = global_state.robots_blue(i).k_pose().x();         // Kalman Pos X
            state.robots_kalman[i].pose.y = global_state.robots_blue(i).k_pose().y();         // Kalman Pos Y
            state.robots_kalman[i].pose.z = global_state.robots_blue(i).k_pose().yaw();       // Kalman Rotation in Z Axis (YAW)

            // blue Robots Kalman predict VELOCITYS
            state.robots_kalman[i].v_pose.x = global_state.robots_blue(i).k_v_pose().x();       // Kalman Vel X
            state.robots_kalman[i].v_pose.y = global_state.robots_blue(i).k_v_pose().y();       // Kalman Vel Y
            state.robots_kalman[i].v_pose.z = global_state.robots_blue(i).k_v_pose().yaw();     // Kalman Vel Rotation in Z Axis (YAW)
*/

            // yellow Robots POSE
            pose.x =  global_state.robots_yellow(i).pose().x();           // Pos X
            pose.y = global_state.robots_yellow(i).pose().y();           // Pos Y
            pose.z =  global_state.robots_yellow(i).pose().yaw();         // Rotation in Z Axis (YAW)

            // yellow Robots VELOCITYS
            v_pose.x = global_state.robots_yellow(i).v_pose().x();         // Vel X
            v_pose.y = global_state.robots_yellow(i).v_pose().y();         // Vel Y
            v_pose.z = global_state.robots_yellow(i).v_pose().yaw();       // Vel Rotation in Z Axis (YAW)

            state.robots[i+3].set_position(pose);
            state.robots[i+3].set_velocity_vector(v_pose);
/*
            // yellow Robots Kalman predict POSE
            state.robots_kalman[i+3].pose.x = global_state.robots_yellow(i).k_pose().x();         // Kalman Pos X
            state.robots_kalman[i+3].pose.y = global_state.robots_yellow(i).k_pose().y();         // Kalman Pos Y
            state.robots_kalman[i+3].pose.z = global_state.robots_yellow(i).k_pose().yaw();       // Kalman Rotation in Z Axis (YAW)

            // yellow Robots Kalman predict VELOCITYS
            state.robots_kalman[i+3].v_pose.x = global_state.robots_yellow(i).k_v_pose().x();       // Kalman Vel X
            state.robots_kalman[i+3].v_pose.y = global_state.robots_yellow(i).k_v_pose().y();       // Kalman Vel Y
            state.robots_kalman[i+3].v_pose.z = global_state.robots_yellow(i).k_v_pose().yaw();     // Kalman Vel Rotation in Z Axis (YAW)
*/
        }
    }

    return state;
}
