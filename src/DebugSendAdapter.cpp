//
// Created by manoel on 16/04/18.
//

#include <DebugSenderAdapter.h>

DebugSendAdapter::DebugSendAdapter(string teamColor, bool isDebug) {
    this->teamColor = teamColor;
    this->isDebug = isDebug;

    if(isDebug)
        createSocketDebug();
}

void DebugSendAdapter::createSocketDebug() {
    if(this->teamColor == "yellow")
        interfaceDebug.createSendDebugTeam1(&this->globalDebug);
    else
        interfaceDebug.createSendDebugTeam2(&this->globalDebug);

}

void DebugSendAdapter::sendDebug(common::Debug debug) {

    if(isDebug) {

        globalDebug = vss_debug::Global_Debug();

        // Add step pose, if exists
        for (int i = 0; i < 3; i++) {
            vss_debug::Pose *steps = globalDebug.add_step_poses();
            steps->set_id(i);
            steps->set_x(debug.robots_step_pose[i].x);
            steps->set_y(debug.robots_step_pose[i].y);
            steps->set_yaw(debug.robots_step_pose[i].z);
        }

        // Add final pose, if exists
        for (int i = 0; i < 3; i++) {
            vss_debug::Pose *finals = globalDebug.add_final_poses();
            finals->set_id(i);
            finals->set_x(debug.robots_final_pose[i].x);
            finals->set_y(debug.robots_final_pose[i].y);
            finals->set_yaw(debug.robots_final_pose[i].z);
        }

        for (int i = 0; i < 3; i++) {
            vss_debug::Path *paths = globalDebug.add_paths();
            paths->set_id(i);
            for (uint j = 0; j < debug.robots_path[i].poses.size(); j++) {
                vss_debug::Pose *poses = paths->add_poses();
                poses->set_id(i);
                poses->set_x(debug.robots_path[i].poses.at(j).x);
                poses->set_y(debug.robots_path[i].poses.at(j).y);
                poses->set_yaw(debug.robots_path[i].poses.at(j).z);
            }
        }

        if (teamColor == "yellow") {
            interfaceDebug.sendDebugTeam1();
        } else {
            interfaceDebug.sendDebugTeam2();
        }
    }
}




