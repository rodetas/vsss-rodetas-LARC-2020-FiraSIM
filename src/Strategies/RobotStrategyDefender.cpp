//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>

RobotStrategyDefender::RobotStrategyDefender() = default;

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);

    // Se o robo estiver perto da bola e o robo estiver andando na direcao do eixo y, gira em torno do proprio eixo de acordo com o lado do campo
    if(robot.distanceFrom(state.ball.position) < 7 and abs(robot.vectorSpeed.y) > abs(robot.vectorSpeed.x*2)) {
        if (robot.position.y > state.ball.position.y) {
            c = movimentation.turnLeft(60, 60);
        } else {
            c = movimentation.turnRight(60, 60);
        }
    }

    return c;
}

vss::Pose RobotStrategyDefender::defineTarget() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;
   // se a bola passou da linha de defesa e do zagueiro
    if (state.ball.position.x > (vss::MAX_COORDINATE_X  - 20) * 0.70 and state.ball.position.x-5 > robot.position.x) {

        // coloca o robo pra tras da bola
        target.x = state.ball.projection.x + 10;
        target.y = state.ball.position.y;

        if(target.x > (vss::MAX_COORDINATE_X  - 20) - 20){
            // se esta fora do campo
            target.x = state.ball.position.x;
        }

//        // se a bola passar da linha de defesa, posiciona o robô no canto da area para auxiliar o goleiro
//        if(state.ball.position.y > vss::MAX_COORDINATE_Y / 2) {
//            target.x = (vss::MAX_COORDINATE_X  - 20) - 15;
//            target.y = vss::MAX_COORDINATE_Y - 22;
//        } else {
//            target.x = (vss::MAX_COORDINATE_X  - 20) - 15;
//            target.y = vss::MIN_COORDINATE_Y + 22;
//        }

    } else {
        // se a bola nao passou da linha de defesa e o zagueiro esta atras dela, acompanha a bola no eixo y
        target.x = (vss::MAX_COORDINATE_X  - 20) * 0.70;
        target.y = ballProjection.y;

        // se a bola estiver na parede, evita que o defensor fique preso na parede
        if (ballProjection.y >= (vss::MAX_COORDINATE_Y - 5)) {
            target.y = ballProjection.y - 4;
        } else if (ballProjection.y <= 5) {
            target.y = ballProjection.y + 4;
        }
    }

    // ataca a bola caso ela chegue perto
    if (robot.distanceFrom(state.ball.position) < 20 // bola esta proxima do robo
        and robot.position.x > (vss::MAX_COORDINATE_X  - 20) * 0.60) {// robo so pode atacar ate 60% do campo

        if(state.ball.vectorSpeed.x <= 0) {
            // bola esta indo para o ataque
            target.x = state.ball.projection.x;
            target.y = state.ball.projection.y;
            target.angle = Math::arrivalAngle(target, vss::Point(0, vss::MAX_COORDINATE_Y / 2));
        } else {
            // bola esta indo para defesa
            target.x = state.ball.position.x;
            target.y = state.ball.position.y;
            target.angle = Math::arrivalAngle(target, vss::Point(0, vss::MAX_COORDINATE_Y / 2));

           if(abs(state.ball.vectorSpeed.x) > abs(state.ball.vectorSpeed.y * 1.2)){
                target.x = state.ball.projection.x;
                target.y = state.ball.projection.y;
            }
        }
    }

    //target.x = 75;
    //target.y = 65;

    //target.angle = 0;
        
    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target) {
    std::vector <std::pair<vss::Point, vss::Point>> obstacles;

    if (robot.distanceFrom(target) > 15) {
        //Obstáculos roboôs
        for (auto &r: state.robots) {
            if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
                obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
            }
        }
    }

    //Obstáculos de área do gol
    std::pair <vss::Point, vss::Point> obstacle;

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

        obstacle.first.x = 130;

        obstacle.first.y = 96;
        obstacles.push_back(obstacle);
        obstacle.first.y = 33;
        obstacles.push_back(obstacle);
    }

    UnivectorField univectorField(robot);
    //univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença

    path = univectorField.drawPath(robot, target, obstacles);
    if(univectorField.offTheField){
        obstacles.clear();
    }

    //univectorField.setUnivectorWithoutCurves();

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