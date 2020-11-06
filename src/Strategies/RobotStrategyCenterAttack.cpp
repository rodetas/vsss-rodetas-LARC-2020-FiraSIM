//
//Created by Samuel on 04/10/18
//
#include <Strategies/RobotStrategyCenterAttack.h>
#include <iostream>

RobotStrategyCenterAttack::RobotStrategyCenterAttack(){
    stopCenterAttacker = true;
}

vss::WheelsCommand RobotStrategyCenterAttack::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    if (stopCenterAttacker) {
        c = stopStrategy(c);
    }
    return c;
}

vss::Pose RobotStrategyCenterAttack::defineTarget() {
    vss::Pose target;
    vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y / 2);

    target.x = (vss::MAX_COORDINATE_X  - 20) * 0.4;
    target.y = vss::MAX_COORDINATE_Y * 0.5;

    stopCenterAttacker = true;

    if (state.ball.position.x < (vss::MAX_COORDINATE_X  - 20) * 0.25) {
        if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.5) {
            target.x = (vss::MAX_COORDINATE_X  - 20) * 0.25;
            target.y = vss::MAX_COORDINATE_Y * 0.70;
            target.angle = 0;
        } else {
            target.x = (vss::MAX_COORDINATE_X  - 20) * 0.25;
            target.y = vss::MAX_COORDINATE_Y * 0.30;
            target.angle = 0;
        }
    }
    if (state.ball.position.x < (vss::MAX_COORDINATE_X  - 20) * 0.25) {
        if (state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
            state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 && state.ball.projection.y > state.ball.position.y) {
            if(Math::distancePoint(state.ball.position,robot.position)>= 5){
                target.x = state.ball.projection.x;
                target.y = (state.ball.projection.y + 2);
            }else{
                target.x = centerGoal.x;
                target.y = centerGoal.y;
            }

            vss::Point targetPoint(target.x, target.y);
            target.angle = Math::arrivalAngle(targetPoint, centerGoal);

            stopCenterAttacker = false;

        } else if (state.ball.position.y < vss::MAX_COORDINATE_Y * 0.70 &&
                   state.ball.position.y > vss::MAX_COORDINATE_Y * 0.3 &&
                   state.ball.projection.y < state.ball.position.y) {
            if(Math::distancePoint(state.ball.position,robot.position)>= 5){
                target.x = state.ball.projection.x;
                target.y = (state.ball.projection.y - 2);
            }else{
                target.x = centerGoal.x;
                target.y = centerGoal.y;
            }


            vss::Point targetPoint(target.x, target.y);
            target.angle = Math::arrivalAngle(targetPoint, centerGoal);

            stopCenterAttacker = false;
        }
    }


    return target;

}


float RobotStrategyCenterAttack::applyUnivectorField(vss::Pose target) {
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    if (robot.distanceFrom(target) > 15) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }
    UnivectorField univectorField;

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        univectorField.setUnivectorWithoutCurves();
        obstacles.clear();
    }

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}