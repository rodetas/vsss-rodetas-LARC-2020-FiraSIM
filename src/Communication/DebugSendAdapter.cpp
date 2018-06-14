//
// Created by manoel on 16/04/18.
//

#include <Communication/DebugSenderAdapter.h>

DebugSendAdapter::DebugSendAdapter(vss::TeamType teamColor, bool isDebug) {
    this->teamColor = teamColor;
    this->isDebug = isDebug;

    if(isDebug)
        createSocketDebug();
}

void DebugSendAdapter::createSocketDebug() {
    if(this->teamColor == vss::TeamType::Yellow)
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
            steps->set_x(debug.robotsStepPose[i].x);
            steps->set_y(debug.robotsStepPose[i].y);
            steps->set_yaw(debug.robotsStepPose[i].z);
        }

        // Add final pose, if exists
        for (int i = 0; i < 3; i++) {
            vss_debug::Pose *finals = globalDebug.add_final_poses();
            finals->set_id(i);
            finals->set_x(debug.robotsFinalPose[i].x);
            finals->set_y(debug.robotsFinalPose[i].y);
            finals->set_yaw(debug.robotsFinalPose[i].z);
        }

        for (int i = 0; i < 3; i++) {
            vss_debug::Path *paths = globalDebug.add_paths();
            paths->set_id(i);
            for (uint j = 0; j < debug.robotsPath[i].poses.size(); j++) {
                vss_debug::Pose *poses = paths->add_poses();
                poses->set_id(i);
                poses->set_x(debug.robotsPath[i].poses.at(j).x);
                poses->set_y(debug.robotsPath[i].poses.at(j).y);
                poses->set_yaw(debug.robotsPath[i].poses.at(j).z);
            }
        }

        if (teamColor == vss::TeamType::Yellow) {
            interfaceDebug.sendDebugTeam1();
        } else {
            interfaceDebug.sendDebugTeam2();
        }
    }
}




