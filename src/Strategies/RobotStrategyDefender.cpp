//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>

RobotStrategyDefender::RobotStrategyDefender() = default;

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);

    //Se o robo estiver perto da bola, gira em torno do proprio eixo de acordo com o lado do campo
    if(robot.distanceFrom(state.ball.position) < (9)){
        if(state.ball.position.y > vss::MAX_COORDINATE_Y / 2) {
            c = movimentation.turnRight(80, 80);
        }
        else{
            c = movimentation.turnLeft(80, 80);
        }
    }
    return c;
}

vss::Pose RobotStrategyDefender::defineTarget() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    //Se a bola passar da linha de defesa, posiciona o robô no canto da area para auxiliar o goleiro
    if(state.ball.position.y > vss::MAX_COORDINATE_Y / 2){
        if (state.ball.position.x > vss::MAX_COORDINATE_X * 0.75) {
            target.x = vss::MAX_COORDINATE_X - 15;
            target.y = vss::MAX_COORDINATE_Y - 22;
        } else {
            //Linha de defesa lado Direito
            // posiciona defensor na frente da area
            target.x = vss::MAX_COORDINATE_X * 0.75;
            // se a bola estiver na parede, evita que o defensor fique preso na parede
            if (ballProjection.y >= (vss::MAX_COORDINATE_Y - 5)) {
                target.y = ballProjection.y - 4;
            }else{
                target.y = ballProjection.y;
            }
        }
    }else{
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
            }else{
                target.y = ballProjection.y;
            }
        }

    }

    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target){
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;

    if(robot.distanceFrom(target) > 15){
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

vss::WheelsCommand RobotStrategyDefender::stopStrategy(vss::WheelsCommand command) {
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