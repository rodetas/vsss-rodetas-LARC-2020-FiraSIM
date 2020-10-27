#include <Kernel.h>

Kernel::Kernel() {
    isPlaying = true;
    isTestingTransmission = false;
    isFreeBall = false;
    isRunning = true;

    positionStatus = PositionStatus::None;
};

void Kernel::loop() {
    bool my_robots_are_yellow = false;
    if(Config::controlWindow)
        threadWindowControl = new thread(std::bind(&Kernel::windowThreadWrapper, this));
    cout << "team color: "<<Config::teamColor<<endl;
    if (Config::teamColor == 0){
        my_robots_are_yellow = true;
    }
    else{
        my_robots_are_yellow = false;
    }
    RobotStrategyFactory coach;
    RoboCupSSLClient visionClient("224.5.23.2", 10020);
    //GrSim_Client commandClient("127.0.0.1", 20011);
    fira_message::sim_to_ref::Environment packet;

    visionClient.open(false);
while(true){
    if (visionClient.receive(packet)) {
            printf("-----Received Wrapper Packet---------------------------------------------\n");
            //see if the packet contains a robot detection frame:
            if (packet.has_frame()) {
                fira_message::Frame detection = packet.frame();


                int robots_blue_n =  detection.robots_blue_size();
                int robots_yellow_n =  detection.robots_yellow_size();

                //Ball info:

                fira_message::Ball ball = detection.ball();
                printf("-Ball:  POS=<%9.2f,%9.2f> \n",ball.x(),ball.y());

                //Blue robot info:
                for (int i = 0; i < robots_blue_n; i++) {
                    fira_message::Robot robot = detection.robots_blue(i);
                    printf("-Robot(B) (%2d/%2d): ",i+1, robots_blue_n);
                    visionClient.printRobotInfo(robot);

                    /*if(!my_robots_are_yellow){
                        if(robot.x() <= 0){
                            commandClient.sendCommand(10, 10, my_robots_are_yellow, i);
                        }else{
                            commandClient.sendCommand(-10, -10, my_robots_are_yellow, i);
                        }
                    }*/
                }

                //Yellow robot info:
                for (int i = 0; i < robots_yellow_n; i++) {
                    fira_message::Robot robot = detection.robots_yellow(i);
                    printf("-Robot(Y) (%2d/%2d): ",i+1, robots_yellow_n);
                    visionClient.printRobotInfo(robot);

                    /*if(my_robots_are_yellow){
                        if(robot.x() <= 0){
                            commandClient.sendCommand(10, 10, my_robots_are_yellow, i);
                        }else{
                            commandClient.sendCommand(-10, -10, my_robots_are_yellow, i);
                        }
                    }*/
                }

            }

            //see if packet contains geometry data:
            if (packet.has_field()){
                printf("-[Geometry Data]-------\n");

                const fira_message::Field & field = packet.field();
                printf("Field Dimensions:\n");
                printf("  -field_length=%f (mm)\n",field.length());
                printf("  -field_width=%f (mm)\n",field.width());
                printf("  -goal_width=%f (mm)\n",field.goal_width());
                printf("  -goal_depth=%f (mm)\n",field.goal_depth());
            }
        }
    }
    }
/*
    StateReceiverAdapter receiveInterface(Config::teamColor, Config::changeSide);
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);

    vector<RodetasRobot> robots;

    robots.emplace_back(RodetasRobot(0, MindSet::SingleAttackerStrategy, new RobotStrategySingleAttack()));
    robots.emplace_back(RodetasRobot(1, MindSet::DefenderStrategy, new RobotStrategyDefender()));
    robots.emplace_back(RodetasRobot(2, MindSet::GoalKeeperStrategy, new RobotStrategyGoal()));

    vector<vss::WheelsCommand> commands(3);

    RodetasState state;

    vss::Debug debug;
    debug.paths.resize(3);
    debug.finalPoses.resize(3);
    debug.stepPoints.resize(3);

    while (isRunning) {

        // method which waits and receives a new state from simulator or vision
        state = receiveInterface.receiveState();

        for (unsigned int i = 0; i < robots.size(); i++) {
            RodetasRobot &robot = robots[i];

            robot.updateSelfState(state.robots[i]);
            std::cout<<state.robots[i].position << "---";
            robot.updateState(state);
            robot.calcAction();

            commands[i] = robot.getCommand();

            //debug.finalPoses[i] = robot.getFinalPose();
            debug.stepPoints[i] = robot.getStepPoint();
            debug.paths[i] = robot.getPath();
        }

        std::cout<<std::endl;

        coach.manage(robots, state, Config::playersSwap, isFreeBall, positionStatus);

        sendInterface.sendCommands(robots, isPlaying, isTestingTransmission);
        debugInterface.sendDebug(debug);
    }*/

    /*if(Config::controlWindow)
        threadWindowControl->detach();
}*/

void Kernel::windowThreadWrapper() {

    windowControl.signalUpdatePlaying.connect(sigc::mem_fun(this, &Kernel::updatePlayingState));
    windowControl.signalUpdateTesting.connect(sigc::mem_fun(this, &Kernel::updateTestingState));
    windowControl.signalChangeFunction.connect(sigc::mem_fun(this, &Kernel::freeBallPositions));
    windowControl.signalCloseWindow.connect(sigc::mem_fun(this, &Kernel::exitProgram));
    windowControl.signalPositioning.connect(sigc::mem_fun(this, &Kernel::automaticPositioning));

    windowControl.start();
}

void Kernel::automaticPositioning(PositionStatus posStatus){
    if(this->positionStatus != PositionStatus::None) this->positionStatus = PositionStatus::None;
    else this->positionStatus = posStatus;
}

void Kernel::freeBallPositions(bool isFreeBall){
    this->isFreeBall = isFreeBall;
}

void Kernel::updatePlayingState(bool playing) {
    this->isPlaying = playing;

    if(isFreeBall && isPlaying) isFreeBall = false;
}

void Kernel::updateTestingState(bool testing) {
    this->isTestingTransmission = testing;
}

void Kernel::exitProgram(){
    isRunning = false;
    exit(0);
}
