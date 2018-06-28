//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>
#include <iostream>
using namespace std;

RobotStrategyDefender::RobotStrategyDefender() = default;

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);

    return c;
}

vss::Pose RobotStrategyDefender::defineTarget() {

    vss::Pose target;
    vss::Point ballProjection = state.ball.projection;

    // altera o ponto de destino dependendo do sentido da bola, evitando bater no outro robo
    /*if (robot.position.x < vss::MAX_COORDINATE_X * 0.4) {
        if (robot.position.y > vss::MAX_COORDINATE_Y / 2) {
            if (ballProjection.y < state.ball.position.y) {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.5, vss::MAX_COORDINATE_Y * 0.2, 0);
                cout<<"entrando1"<<endl;
            } else {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.5, vss::MAX_COORDINATE_Y * 0.8, 0);
                cout<<"entrando2"<<endl;
            }
        } else {
            if (ballProjection.y < state.ball.position.y) {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.5, vss::MAX_COORDINATE_Y * 0.2, 0);
                cout<<"entrando3"<<endl;
            } else {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.5, vss::MAX_COORDINATE_Y * 0.8, 0);
                cout<<"entrando4"<<endl;
            }
        }

    }
    */
    // altera o ponto de destino dependendo do sentido da bola, evitando bater no outro robo, posicionando perto da area inimiga
    /*
    if(state.ball.position.x > state.robots.position.x)
    {
        target= vss::Pose(vss::MAX_COORDINATE_X /2, vss::MAX_COORDINATE_Y/2, 0); //Se não tiver com a bola, posiciona defensor no meio do campo
    }
    */
    if((ballProjection.x < vss::MAX_COORDINATE_X / 3.5))
    {
        if (robot.position.x < vss::MAX_COORDINATE_X * 0.6) {
            if (robot.position.x > 34) {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y / 2, 0);
            } else {
                if (robot.position.y < vss::MAX_COORDINATE_Y / 2) {
                    if (ballProjection.y > state.ball.position.y) {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.15, 0);
                        cout << "entrando1" << endl;
                    } else {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.75, 0);
                        cout << "entrando2" << endl;
                    }
                } else {
                    if (ballProjection.y > state.ball.position.y) {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.15, 0);
                        cout << "entrando3" << endl;
                    } else {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.75, 0);
                        cout << "entrando4" << endl;
                    }
                }
            }

        }
    }
    else {
        target = vss::Pose(vss::MAX_COORDINATE_X/2, vss::MAX_COORDINATE_Y /2, 0);
    }


      //Se a bola estiver no ataque, posiciona o robo perto/dentro da area inimiga
      //target = vss::Pose(vss::MAX_COORDINATE_X *0.3, vss::MAX_COORDINATE_Y / 2, 0);
      /*  //Se a bola estiver no ataque, posiciona o robo perto/dentro da area inimiga
        if (ballProjection.x < vss::MAX_COORDINATE_X / 2) {
          cout<<"entrando5"<<endl;
            if (ballProjection.y > vss::MAX_COORDINATE_Y / 2)
            {
                target = vss::Pose((-vss::MAX_COORDINATE_X/2 +20), (vss::MAX_COORDINATE_Y /2), 0);
                cout<<"Coordenada de x "<<vss::MAX_COORDINATE_X<<endl;
                cout<<"ball < coordenada y"<<target<<endl;
            } else {
                target = vss::Pose((-vss::MAX_COORDINATE_X/2 +20), (vss::MAX_COORDINATE_Y/2), 0);
                cout<<"ball > coordenada y"<<target<<endl;
                cout<<"Coordenada de x "<<vss::MAX_COORDINATE_X<<endl;
            }
        }
        */

    /*else {
        // se a bola esta no ataque posiciona o robo no meio do campo
        target = vss::Pose(vss::MAX_COORDINATE_X / 2, vss::MAX_COORDINATE_Y / 2, 0);
    }
    */

    // posiciona o robo na defesa para facilitar a troca de posicao com o goleiro
    if (ballProjection.x > vss::MAX_COORDINATE_X / 2) {
        if (ballProjection.y > vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.7, vss::MAX_COORDINATE_Y * 0.2, 0);
        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.7, vss::MAX_COORDINATE_Y * 0.8, 0);
        }
    }

    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target) {

    vss::Point arrivalOrientation = defineArrivalOrientation(target);

    std::vector<std::pair<vss::Point, vss::Point>> obstacles;
    for (auto &r: state.robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
            obstacles.push_back(std::make_pair(r.position, r.vectorSpeed));
        }
    }

    UnivectorField univectorField(2, 0.12, 4.5, 4.5);
    path = univectorField.drawPath(robot, target, arrivalOrientation, obstacles);
    return univectorField.defineFi(robot, target, arrivalOrientation, obstacles);
}

vss::Point RobotStrategyDefender::defineArrivalOrientation(vss::Pose target) {
    vss::Point goal(0, 75);
    vss::Point arrivalOrientation;

    if((target.x == state.ball.projection.x) && (target.y == state.ball.projection.y)){

        if(target.y < 13){
            arrivalOrientation.x = target.x - 10;
            arrivalOrientation.y = target.y - 7;
            return arrivalOrientation;
        }

        if(target.y > 115){
            arrivalOrientation.x = target.x - 10;
            arrivalOrientation.y = target.y + 7;
            return arrivalOrientation;
        }

        if(target.x > 140 && target.y < 48){
            arrivalOrientation.x = target.x;
            arrivalOrientation.y = target.y - 10;
            return arrivalOrientation;
        }

        if(target.x > 140 && target.y > 86){
            arrivalOrientation.x = target.x;
            arrivalOrientation.y = target.y + 10;
            return arrivalOrientation;
        }

        float numerator = abs(target.y - goal.y);
        float denominator = abs(target.x - goal.x);
        float tg = (numerator/denominator);
        float deltaX = 10 * (1/sqrt(1 + (tg*tg)));
        float deltaY = tg * deltaX;

        if(target.y < goal.y){
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y + deltaY;
        }else{
            arrivalOrientation.x = target.x - deltaX;
            arrivalOrientation.y = target.y - deltaY;
        }
        return arrivalOrientation;
    } else{
        arrivalOrientation.x = target.x - 10;
        arrivalOrientation.y = target.y;
        return arrivalOrientation;
    }
}
