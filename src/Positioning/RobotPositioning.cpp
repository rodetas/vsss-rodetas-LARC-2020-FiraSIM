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

    // define o valor de fi com base no target do robo
    float fi = this->applyUnivectorField(target);

    // define a velocidade do robo com base no valor do fi
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

// Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para o ponto passado
vss::WheelsCommand RobotPositioning::stopStrategy(vss::WheelsCommand c, vss::Point point) {

    float maxDistance = 12; // 12 cm
    double distanceTarget = robot.distanceFrom(target);


    if (distanceTarget < maxDistance) {
        c.leftVel = c.leftVel * (distanceTarget / maxDistance);
        c.rightVel = c.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < 4) {

        if (robot.cosFrom(point) < -0.8 || robot.cosFrom(point) > 0.8) {
            c = movimentation.stop();

        } else {

            if (robot.sinFrom(point) > 0) {
                c = movimentation.turnRight(10, 10);
            } else {
                c = movimentation.turnLeft(10, 10);
            }
        }
    }

    return c;
}