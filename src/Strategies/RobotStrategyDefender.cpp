//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>
#include <Domain/Constants.h>

RobotStrategyDefender::RobotStrategyDefender(){
    mindSet = MindSet::DefenderStrategy;
    stopInPoint = true;
}

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    if (stopInPoint) c = stopStrategy(c);
    c = cornerStrategy(c);

    // Se o robo estiver perto da bola e o robo estiver andando na direcao do eixo y, gira em torno do proprio eixo de acordo com o lado do campo
    if (robot.distanceFrom(state.ball.position) < 7 and abs(robot.vectorSpeed.y) > abs(robot.vectorSpeed.x*2)) {
        if (robot.position.y > state.ball.position.y) {
            c = movimentation.turnLeft(100,100);
        } else {
            c = movimentation.turnRight(100,100);
        }
    }

    return c;
}

vss::Pose RobotStrategyDefender::defineTarget() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;
    vss::Point centerGoal(0, vss::MAX_COORDINATE_Y/2);

    stopInPoint = false;

    // se a bola passou da linha de defesa e do zagueiro
    if (state.ball.position.x > vss::MAX_COORDINATE_X * 0.70) {

        target.x = state.ball.position.x;
        target.y = state.ball.position.y;

        target.angle = 0;

        if ((target.x > vss::MAX_COORDINATE_X * 0.88) && (target.y < vss::MAX_COORDINATE_Y * 0.37)) {
            target.angle = (3 * M_PI) / 2;
        }
        if ((target.x > vss::MAX_COORDINATE_X * 0.88) && (target.y > vss::MAX_COORDINATE_Y * 0.66)) {
            target.angle = M_PI_2;
        }

    } else {
        stopInPoint = true;

        // se a bola nao passou da linha de defesa e o zagueiro esta atras dela, acompanha a bola no eixo y
        target.x = vss::MAX_COORDINATE_X * 0.70;
        target.y = ballProjection.y;

        // se a bola estiver na parede, evita que o defensor fique preso na parede
        if (ballProjection.y >= (vss::MAX_COORDINATE_Y - 5)) {
            target.y = ballProjection.y - 4;
        } else if (ballProjection.y <= 5) {
            target.y = ballProjection.y + 4;
        }
    }
    
    // ataca a bola caso ela chegue perto
    if (robot.position.x > vss::MAX_COORDINATE_X * 0.60) { // robo so pode atacar ate 60% do campo

            if (robot.distanceFrom(state.ball.position) < 20 and robot.position.x > state.ball.position.x) { // bola esta proxima do robo
                stopInPoint = false;

                if (state.ball.vectorSpeed.x <= 0) {
                    // bola esta indo para o ataque
                    target.x = state.ball.projection.x;
                    target.y = state.ball.projection.y;
                    target.angle = Math::arrivalAngle(target, centerGoal);
                } else {
                    // bola esta indo para defesa
                    target.x = state.ball.position.x;
                    target.y = state.ball.position.y;
                    target.angle = Math::arrivalAngle(target, centerGoal);

                    if (abs(state.ball.vectorSpeed.x) > abs(state.ball.vectorSpeed.y * 1.2)) {
                        target.x = state.ball.projection.x;
                        target.y = state.ball.projection.y;
                    }
                }
        }
    }

    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target) {
    std::vector <std::pair<vss::Point, vss::Point>> obstacles;

    if (robot.distanceFrom(target) > 30) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }
//
//    //Obstáculos de área do gol
//    std::pair <vss::Point, vss::Point> obstacle;
//
//    obstacle.second.x = 0;
//    obstacle.second.y = 0;
//
//
//    if (!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
//          robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 - 5) &&
//          robot.position.x > vss::MAX_COORDINATE_X - 25)) {
//
//        obstacle.first.x = 152;
//
//        obstacle.first.y = 38;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 45;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 50;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 55;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 60;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 65;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 70;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 75;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 80;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 85;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 93;
//        obstacles.push_back(obstacle);
//
//        obstacle.first.x = 160;
//
//        obstacle.first.y = 96;
//        obstacles.push_back(obstacle);
//        obstacle.first.y = 33;
//        obstacles.push_back(obstacle);
//    }

    UnivectorField univectorField;
    univectorField.setN(2);
    univectorField.setOrientationPointDistance(5);

    if (state.ball.position.x > robot.position.x and state.ball.position.x > vss::MAX_COORDINATE_X*0.7) {
        // define com curvas caso a bola esteja na area de defesa
        //Seta curva passando parâmetro
        univectorField.setN(2);
        univectorField.setOrientationPointDistance(5);
    } else {
        // define sem curvas caso a bola esteja na frente do robo e a bola esteja na area de ataque
        univectorField.setUnivectorWithoutCurves();
    }

    path = univectorField.drawPath(robot, target, obstacles);
    // nao permite que o zagueiro entre na area
    if (univectorField.insideGoalArea) {
        stopInPoint = true;

        univectorField.setUnivectorWithoutCurves();

        target.x = vss::MAX_COORDINATE_X*0.8;
        if (target.y < vss::MAX_COORDINATE_Y/2) {
            target.y = 25;
        } else {
            target.y = 110;
        }
    }


    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        univectorField.setUnivectorWithoutCurves();
        obstacles.clear();
    }


    this->target = target;
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}

vss::WheelsCommand RobotStrategyDefender::stopStrategy(vss::WheelsCommand command) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    vss::WheelsCommand c = command;
    float maxDistance = (12); // 12 cm
    float distanceTarget = (float) robot.distanceFrom(target);

    if (distanceTarget < maxDistance) {
        c.leftVel = command.leftVel * (distanceTarget / maxDistance);
        c.rightVel = command.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < (4)) {

        if ((robot.angle > 70 && robot.angle < 110) || (robot.angle > 250 && robot.angle < 290)) {
            c = movimentation.stop();
        } else {
            if ((robot.angle > 0 and robot.angle < 90) or (robot.angle > 180 and robot.angle < 270)){
                c = movimentation.turnRight(25, 25);
            } else {
                c = movimentation.turnLeft(25, 25);
            }
        }
    }

    return c;
}