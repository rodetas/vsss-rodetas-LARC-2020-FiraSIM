//
//Created by Samuel on 04/10/18
//
#include <Strategies/RobotStrategyCenterAttack.h>
#include <iostream>
RobotStrategyCenterAttack::RobotStrategyCenterAttack() = default;

vss::WheelsCommand RobotStrategyCenterAttack::specificStrategy(vss::WheelsCommand c) {
    c = cornerStrategy(c);
    c = stopStrategy(c);
    return c;
}

vss::Pose RobotStrategyCenterAttack::defineTargetAndArrivalOrientation(){
    vss::Pose target;
    //vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);

    target.x = vss::MAX_COORDINATE_X*0.4;
    target.y = vss::MAX_COORDINATE_Y*0.5;

    if(state.ball.position.x < vss::MAX_COORDINATE_X*0.25) 
    {
        if(state.ball.position.y < vss::MAX_COORDINATE_Y*0.5)
        {
            target.x = vss:: MAX_COORDINATE_X*0.25;
            target.y = vss:: MAX_COORDINATE_Y*0.70;
        }
        else 
            {
                target.x = vss::MAX_COORDINATE_X*0.25;
                target.y = vss::MAX_COORDINATE_Y*0.30;
            }
    }
     if(state.ball.position.x < vss::MAX_COORDINATE_X*0.25) 
    {
        if(state.ball.position.y > vss::MAX_COORDINATE_Y*0.3 && state.ball.position.y < vss::MAX_COORDINATE_Y*0.70 && state.ball.projection.y > state.ball.position.y)
        {
            target.x = state.ball.projection.x;
            target.y = (state.ball.projection.y + 2);
            
            /*target.x = 0;
            target.y = centerGoal.y;*/
        }
        else if (state.ball.position.y < vss::MAX_COORDINATE_Y*0.70 && state.ball.position.y > vss::MAX_COORDINATE_Y*0.3 && state.ball.projection.y < state.ball.position.y )
                {
                    target.x = state.ball.projection.x;
                    target.y = (state.ball.projection.y-2);
                    
                   /*target.x = 0;
                   target.y = centerGoal.y;
                    */
                }
    }
    //vss::Point centerGoal = vss::Point(0, vss::MAX_COORDINATE_Y/2);
    //vss::Point orientationPoint;

    return target;
  
}


float RobotStrategyCenterAttack::applyUnivectorField(vss::Pose target){
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)){
            obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
        }
    }
    UnivectorField univectorField;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}