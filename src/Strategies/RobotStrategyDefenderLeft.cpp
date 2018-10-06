//
// Created by leonardo on 19/09/18.
//

#include <Strategies/RobotStrategyDefenderLeft.h>

RobotStrategyDefenderLeft::RobotStrategyDefenderLeft() = default;

vss::WheelsCommand RobotStrategyDefenderLeft::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);
    if (robot.distanceFrom(state.ball.position) < (9)) {
        c = movimentation.turnLeft(80, 80);
    }
    return c;
}

vss::Pose RobotStrategyDefenderLeft::defineTarget() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    //Se a bola passar pela linha de defesa, posiciona robo no canto do gol em x
    if (state.ball.position.x > vss::MAX_COORDINATE_X * 0.75) {
        target.x = vss::MAX_COORDINATE_X - 15;
        target.y = vss::MIN_COORDINATE_Y + 22;
    } else {
        // Linha de defesa lado esquerdo
        // posiciona defensor na frente da aréa
        target.x = vss::MAX_COORDINATE_X * 0.75;
        // se a bola estiver na parede, evita que o defensor fique preso na parede
        if (ballProjection.y <= 5) {
            target.y = ballProjection.y + 4;
        }// posiciona defensor na direção da projeção da bola no canto esquerdo ou posiciona no meio do campo em y
        else if (ballProjection.y < vss::MAX_COORDINATE_Y / 2) {
            target.y = ballProjection.y;
        } else {
            target.y = vss::MAX_COORDINATE_Y / 2 - 7;
        }
    }

    return target;
}

float RobotStrategyDefenderLeft::applyUnivectorField(vss::Pose target) {
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    if (robot.distanceFrom(target) > 15) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
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

    UnivectorField univectorField;
    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}

vss::WheelsCommand RobotStrategyDefenderLeft::stopStrategy(vss::WheelsCommand command) {
    // Para o robo quando atinge o target, alem disso, rotaciona de forma que esteja sempre virado para a bola

    vss::WheelsCommand c = command;
    float maxDistance = (12); // 12 cm
    float distanceTarget = (float) robot.distanceFrom(target);

/*	REVER VELOCIDADE
	if(robot.getVelocity() > image_size.x * (0.05)){
		maxDistance = 24; // 24 cm
	}
 */
    if (distanceTarget < maxDistance) {
        c.leftVel = command.leftVel * (distanceTarget / maxDistance);
        c.rightVel = command.rightVel * (distanceTarget / maxDistance);
    }

    if (distanceTarget < (4)) {

        if ((robot.angle > 80 && robot.angle < 120) || (robot.angle > 260 && robot.angle < 300)) {
            c = movimentation.stop();
        } else {
            c = movimentation.turnRight(10, 10);
        }
    }

    return c;
}