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
    command = movimentation.movePlayers(robot, fi, RobotSpeed::SLOW);

    // define as estrategias que serao aplicadas para o robo - esta implementado em todas as classes filhas
    command = this->specificStrategy(command);

    return command;
}

float RobotPositioning::applyUnivectorField(vss::Pose target) {

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    //Se o target for a bola ou sua projeção e o robo estiver longe, desvia de todos
    if(robot.distanceFrom(target) > 15){
        //Obstáculos robôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.emplace_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }

    UnivectorField univectorField;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);

}
