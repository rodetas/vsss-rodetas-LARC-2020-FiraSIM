//
// Created by manoel on 31/08/18.
//

#include <Positioning/RobotPositioning.h>

vss::WheelsCommand RobotPositioning::applyStrategy(RobotState r, RodetasState s, RobotStrategyBase base) {
    this->robot = r;
    this->state = s;
    this->strategyBase = base;

    // define qual o target do robo
    target = this->defineTargetAndArrivalOrientation();

    float fi = this->applyUnivectorField(target);

    // defines robot's pwm
    command = movimentation.movePlayers(robot, target, fi);

    return command;

}

float RobotPositioning::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    //Se o target for a bola ou sua projeção e o robo estiver longe, desvia de todos
    if ((target.x == state.ball.position.x && target.y == state.ball.position.y) || (target.x == state.ball.projection.x && target.y == state.ball.position.y)) {
        if(robot.distanceFrom(target) > 15){
            //Obstáculos roboôs
            for (auto &r: state.robots) {
                if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                    obstacles.emplace_back(std::make_pair(r.position, r.vectorSpeed));
                }
            }
        }
    }


    //Obstáculos de área do gol
    std::pair<vss::Point, vss::Point> obstacle;

    obstacle.second.x = 0;
    obstacle.second.y = 0;


    if(!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
         robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 -5) &&
         robot.position.x > vss::MAX_COORDINATE_X - 25)){

        obstacle.first.x = 152;

        obstacle.first.y = 38;
        obstacles.push_back(obstacle);
        obstacle.first.y = 45;
        obstacles.push_back(obstacle);
        obstacle.first.y = 50;
        obstacles.push_back(obstacle);
        obstacle.first.y = 55;
        obstacles.push_back(obstacle);
        obstacle.first.y = 60;
        obstacles.push_back(obstacle);
        obstacle.first.y = 65;
        obstacles.push_back(obstacle);
        obstacle.first.y = 70;
        obstacles.push_back(obstacle);
        obstacle.first.y = 75;
        obstacles.push_back(obstacle);
        obstacle.first.y = 80;
        obstacles.push_back(obstacle);
        obstacle.first.y = 85;
        obstacles.push_back(obstacle);
        obstacle.first.y = 93;
        obstacles.push_back(obstacle);

        obstacle.first.x = 160;

        obstacle.first.y = 96;
        obstacles.push_back(obstacle);
        obstacle.first.y = 33;
        obstacles.push_back(obstacle);
    }


    UnivectorField univectorField(2, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);

}
