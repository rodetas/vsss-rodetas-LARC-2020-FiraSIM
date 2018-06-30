//
// Created by manoel on 23/04/18.
//

#include <Strategies/RobotStrategyDefender.h>

RobotStrategyDefender::RobotStrategyDefender() = default;

vss::WheelsCommand RobotStrategyDefender::specificStrategy(vss::WheelsCommand c) {
    c = stopStrategy(c);

    return c;
}

vss::Pose RobotStrategyDefender::defineTargetAndArrivalOrientation() {

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


    //Posiciona atacante no centro do gol adversario
    if ((ballProjection.x < vss::MAX_COORDINATE_X / 3)) {
        if (robot.position.x < vss::MAX_COORDINATE_X * 0.6) {
            if (robot.position.x > 34 &&
                (state.ball.position.x < 30 || state.ball.position.y < 20 || state.ball.position.y > 110)) {
                target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, 67, 0); //Posição na frente do gol adversário
            } else {
                if (robot.position.y < vss::MAX_COORDINATE_Y / 2) {
                    if (ballProjection.y > state.ball.position.y) {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.15, 0);
                    } else {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.75, 0);
                    }
                } else {
                    if (ballProjection.y > state.ball.position.y) {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.15, 0);
                    } else {
                        target = vss::Pose(vss::MAX_COORDINATE_X * 0.3, vss::MAX_COORDINATE_Y * 0.75, 0);
                    }
                }
            }

        }
    } else {
        target = vss::Pose(vss::MAX_COORDINATE_X / 2, vss::MAX_COORDINATE_Y / 2, 0);
    }

    /*
    if (robot.position.x < vss::MAX_COORDINATE_X * 0.4) {

        //if (ballProjection.x > vss::MAX_COORDINATE_X / 2) {
        if (ballProjection.y > vss::MAX_COORDINATE_Y / 2) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y * 0.15, 0);
        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y * 0.75, 0);
        }
    }
     */ //posiciona robo no lado do campo no ataque
    //}
    /*
    if (robot.position.y < vss::MAX_COORDINATE_Y / 2) {
        if (ballProjection.y < state.ball.position.y) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y * 0.15, 0);
            cout<<"entrando1"<<endl;
        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y * 0.75, 0);
            cout<<"entrando2"<<endl;
        }
    } else {
        if (ballProjection.y < state.ball.position.y) {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y * 0.15, 0);
            cout<<"entrando3"<<endl;
        } else {
            target = vss::Pose(vss::MAX_COORDINATE_X * 0.2, vss::MAX_COORDINATE_Y * 0.75, 0);
            cout<<"entrando4"<<endl;
        }
    }
     */

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

    //Orientação pro lado do gol
    arrivalOrientation.x = target.x - 10;
    arrivalOrientation.y = target.y;

    return target;
}

float RobotStrategyDefender::applyUnivectorField(vss::Pose target) {


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
