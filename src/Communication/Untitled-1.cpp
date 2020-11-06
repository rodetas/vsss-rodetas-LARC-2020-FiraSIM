newState.ball.setPosition(Math::conversion(vss::Point(ball.x()*(-1), ball.y())));
                std::cout<<"BOLA(X,Y): "<<Math::conversion(vss::Point(ball.x()*(-1), ball.y())).x  <<", "<<Math::conversion(vss::Point(ball.x()*(-1), ball.y())).y<<std::endl;
                newState.ball.setLinearSpeed(Math::calculateLinearSpeed(ball.vx()*100, ball.vy()*(-1)*100));
                newState.ball.setVectorSpeed(vss::Point(ball.vx()*100, ball.vy()*(-1)*100));
                newState.ball.setProjection(Math::calculateProjection(Math::conversion(vss::Point(ball.x()*(-1), ball.y())), ball.vx()*100, ball.vy()*(-1)*100));

       for(int i = 0; i < robots_blue_n; i++){
            fira_message::Robot firaRobot = detection.robots_blue(i);
            RobotState robot;
            std::cout<<"Velocidade X/Y:"<<firaRobot.vx()*100 <<" / "<<firaRobot.vy()*(-1)*100<<std::endl;
            std::cout<<"Angulo/V. Angular: "<<Math::toDegree(Math::toDomain2Pi(firaRobot.orientation()*(-1)))<<" / "<<firaRobot.vorientation()<<std::endl;
            robot.setPosition(Math::conversion(vss::Point(firaRobot.x()*(-1), firaRobot.y())));
            robot.setProjection(Math::calculateProjection(Math::conversion(vss::Point(firaRobot.x()*(-1), firaRobot.y())), firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setAngle(Math::toDegree(firaRobot.orientation()*(-1)));
            robot.setAngularSpeed(0);
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setVectorSpeed(vss::Point(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            newState.robots.emplace_back(robot);
        }

        for(int i = 0; i < robots_yellow_n; i++){
             fira_message::Robot firaRobot = detection.robots_blue(i);
             RobotState robot;
            std::cout<<"Velocidade X/Y:"<<firaRobot.vx()*100 <<" / "<<firaRobot.vy()*(-1)*100<<std::endl;
            std::cout<<"Angulo/V. Angular: "<<Math::toDegree(Math::toDomain2Pi(firaRobot.orientation()*(-1)))<<" / "<<firaRobot.vorientation()<<std::endl;
            robot.setPosition(Math::conversion(vss::Point(firaRobot.x()*(-1), firaRobot.y())));
            robot.setProjection(Math::calculateProjection(Math::conversion(vss::Point(firaRobot.x()*(-1), firaRobot.y())), firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setAngle(Math::toDegree(firaRobot.orientation()*(-1)));
            robot.setAngularSpeed(0);
            robot.setLinearSpeed(Math::calculateLinearSpeed(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            robot.setVectorSpeed(vss::Point(firaRobot.vx()*100, firaRobot.vy()*(-1)*100));
            newState.robots.emplace_back(robot);
        }