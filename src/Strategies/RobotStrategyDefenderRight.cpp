//
// Created by leonardo on 19/09/18.
//

#include <Strategies/RobotStrategyDefenderRight.h>
RobotStrategyDefenderRight::RobotStrategyDefenderRight() = default;

vss::WheelsCommand RobotStrategyDefenderRight::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);

    //Se o robo estiver perto da bola, gira em torno do proprio eixo
    if(robot.distanceFrom(state.ball.position) < (8.5)){
        c = movimentation.turnRight(80, 80);
    }
    return c;
}

vss::Pose RobotStrategyDefenderRight::defineTargetAndArrivalOrientation() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    //Se a bola passar pela linha de defesa, posiciona robo no canto do gol em x
    if(state.ball.position.x > vss::MAX_COORDINATE_X * 0.75){
        target.x = vss::MAX_COORDINATE_X - 15;
        target.y = vss::MAX_COORDINATE_Y - 25;
    }
    else {
        //Linha de defesa lado Direito
        // posiciona defensor na frente da area
        target.x = vss::MAX_COORDINATE_X * 0.75;
        // se a bola estiver na parede, evita que o defensor fique preso na parede
        if (ballProjection.y >= (vss::MAX_COORDINATE_Y - 5)) {
            target.y = ballProjection.y - 6;
        }
            // posiciona defensor na direção da projeção da bola no canto direito ou posiciona no meio do campo em y
        else if (ballProjection.y > vss::MAX_COORDINATE_Y / 2) {
            target.y = ballProjection.y;
        } else {
            target.y = vss::MAX_COORDINATE_Y / 2 + 7;
        }
    }

    //Orientação pro lado do gol
    target.angle = 0;

    return target;
}

float RobotStrategyDefenderRight::applyUnivectorField(vss::Pose target){
    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)){
            obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
        }
    }
    UnivectorField univectorField;
    univectorField.setUnivectorWithoutCurves(); // faz com que o robô ande sempre reto  fazendo com que o arrivalOrientation não faça diferença
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
