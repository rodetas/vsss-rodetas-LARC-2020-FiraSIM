//
// Created by leonardo on 19/09/18.
//

#include <Strategies/RobotStrategyDefenderRight.h>

RobotStrategyDefenderRight::RobotStrategyDefenderRight() = default;

vss::WheelsCommand RobotStrategyDefenderRight::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);

    //Se o robo estiver perto da bola, gira em torno do proprio eixo
    if (robot.distanceFrom(state.ball.position) < (9) and robot.position.y < state.ball.position.y) {
        c = movimentation.turnRight(60, 60);
    } else if (robot.distanceFrom(state.ball.position) < (9) and robot.position.y > state.ball.position.y) {
        c = movimentation.turnLeft(60, 60);
    }

    return c;
}

vss::Pose RobotStrategyDefenderRight::defineTarget() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    // Se a bola passar pela linha de defesa, posiciona robo no canto do gol em x
    if (state.ball.position.x > (vss::MAX_COORDINATE_X  - 20) * 0.75) {
        target.x = (vss::MAX_COORDINATE_X  - 20) - 15;
        target.y = vss::MAX_COORDINATE_Y - 22;

        if(state.ball.position.y > vss::MAX_COORDINATE_Y/2) {
            target.x = state.ball.position.x + 5;
            target.y = state.ball.position.y;
        }

//        if(state.ball.position.y > vss::MAX_COORDINATE_Y/2 and state.ball.position.x > robot.position.x){
//            target.x = state.ball.position.x+5;
//            target.y = state.ball.position.y;
//        }

        if(Math::distancePoint(state.ball.position, robot.position) < 9){
            target.x = state.ball.position.x;
            target.y = state.ball.position.y;
        }

    } else {
        // Linha de defesa lado Direito
        // posiciona defensor na frente da area
        target.x = (vss::MAX_COORDINATE_X  - 20) * 0.75;

        if (ballProjection.y >= (vss::MAX_COORDINATE_Y - 5)) {
            // se a bola estiver na parede, evita que o defensor fique preso na parede
            target.y = ballProjection.y - 4;

        } else if (ballProjection.y > vss::MAX_COORDINATE_Y / 2) {
            // posiciona defensor na direção da projeção da bola no canto direito
            target.y = ballProjection.y;

        } else {
            // posiciona no meio do campo em y
            target.y = vss::MAX_COORDINATE_Y / 2 + 7;
        }

        if(Math::distancePoint(state.ball.position, robot.position) < 20
        and robot.position.x > (vss::MAX_COORDINATE_X  - 20) * 0.60
        and robot.position.x > state.ball.position.x){
            target.x = state.ball.position.x;
            target.y = state.ball.position.y;
        }
    }

    return target;
}

float RobotStrategyDefenderRight::applyUnivectorField(vss::Pose target) {
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


    if (!(robot.position.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2 + 5) &&
          robot.position.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 - 5) &&
          robot.position.x > (vss::MAX_COORDINATE_X  - 20) - 25)) {

        obstacle.first.x = 132;

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

        obstacle.first.x = 140;

        obstacle.first.y = 96;
        obstacles.push_back(obstacle);
        obstacle.first.y = 33;
        obstacles.push_back(obstacle);
    }

    UnivectorField univectorField(robot);
    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        obstacles.clear();
    }

    path = univectorField.drawPath(robot, target, obstacles);
    return univectorField.defineFi(robot, target, obstacles);
}

vss::WheelsCommand RobotStrategyDefenderRight::stopStrategy(vss::WheelsCommand command) {
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
