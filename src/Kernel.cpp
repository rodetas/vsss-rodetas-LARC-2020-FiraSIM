#include <Kernel.h>

#define UDP_ADDRESS "224.0.0.1"
#define REFEREE_PORT 10003
#define REPLACER_PORT 10004

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
     if (Config::teamColor == 0){
        my_robots_are_yellow = true;
    }
    else{
        my_robots_are_yellow = false;
    }
    RobotStrategyFactory coach;
    RoboCupSSLClient visionClient("224.0.0.1", 10002);
    
    fira_message::sim_to_ref::Environment packet;
    visionClient.open(false);

    
    StateReceiverAdapter receiveInterface(Config::teamColor, Config::changeSide);
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);
    vector<RodetasRobot> robots;

    QUdpSocket *replacerSocket = new QUdpSocket();
    QUdpSocket *refereeClient = new QUdpSocket();

    // Performing connection to send Replacer commands
    if(replacerSocket->isOpen())
        replacerSocket->close();

    replacerSocket->connectToHost(UDP_ADDRESS, REPLACER_PORT, QIODevice::WriteOnly, QAbstractSocket::IPv4Protocol);
    std::cout << "[Example] Connected to REPLACER socket in port " << REPLACER_PORT << " and address = " << UDP_ADDRESS << ".\n";

    // Perfoming connection to receive Referee commands
    // binding port
    if(refereeClient->bind(QHostAddress::AnyIPv4, REFEREE_PORT, QUdpSocket::ShareAddress) == false){
        std::cout << "[ERROR] Failed to bind referee client =(" << std::endl;
        exit(-1);
    }
    // connecting to multicast group in UDP_ADDRESS
    if(refereeClient->joinMulticastGroup(QHostAddress(UDP_ADDRESS)) == false){
        std::cout << "[ERROR] Failed to join VSSReferee multicast group =(" << std::endl;
        exit(-1);
    }
    std::cout << "[Example] Connected to REFEREE socket in port " << REFEREE_PORT << " and address = " << UDP_ADDRESS << ".\n";
    

    robots.emplace_back(RodetasRobot(0, MindSet::AttackerStrategy, new RobotStrategyAttack()));
    robots.emplace_back(RodetasRobot(1, MindSet::DefenderStrategy, new RobotStrategyDefender()));
    robots.emplace_back(RodetasRobot(2, MindSet::GoalKeeperStrategy, new RobotStrategyGoal()));

    vector<vss::WheelsCommand> commands(3);

    RodetasState state;

    //vss::Debug debug;
    //debug.paths.resize(3);
    //debug.finalPoses.resize(3);
    //debug.stepPoints.resize(3);


    while (isRunning) {
        VSSRef::ref_to_team::VSSRef_Command command;
        bool received = false;
        char *buffer = new char[65535];
        long long int packetLength = 0;

        while(refereeClient->hasPendingDatagrams()){
            // Parse message to protobuf
            packetLength = refereeClient->readDatagram(buffer, 65535);
            if(command.ParseFromArray(buffer, int(packetLength)) == false){
                std::cout << "[ERROR] Referee command parsing error =(" << std::endl;
                exit(-1);
            }

            // If received command, let's debug it
            //std::cout << "[Example] Succesfully received an command from ref: " << getFoulNameById(command.foul()).toStdString() << " for team " << getTeamColorNameById(command.teamcolor()).toStdString() << std::endl;
            //std::cout << getQuadrantNameById(command.foulquadrant()).toStdString() << std::endl;
            if(command.foul() == VSSRef::Foul::STOP){
                Kernel::updatePlayingState(false);
            }
            if(command.foul() == VSSRef::Foul::GAME_ON){
                Kernel::updatePlayingState(true);
            }

            // Showing timestamp
            std::cout << "Timestamp: " << command.timestamp() << std::endl;

            // Showing half
            //std::cout << "Half: " << getHalfNameById(command.gamehalf()).toStdString() << std::endl;

            // Now let's send an placement packet to it

            // First creating an placement command for the blue team
            if(!my_robots_are_yellow){
            VSSRef::team_to_ref::VSSRef_Placement placementCommandBlue;
            VSSRef::Frame *placementFrameBlue = new VSSRef::Frame();
            placementFrameBlue->set_teamcolor(VSSRef::Color::BLUE);
            /*for(int x = 0; x < 3; x++){
                VSSRef::Robot *robot = placementFrameBlue->add_robots();
                robot->set_robot_id(static_cast<uint32_t>(x));
                robot->set_x(0.5);
                robot->set_y(-0.2 + (0.2 * x));
                robot->set_orientation(0.0);
            }*/
            //placementCommandBlue.set_allocated_world(placementFrameBlue);

            // Sending blue
            std::string msgBlue;
            placementCommandBlue.SerializeToString(&msgBlue);
            if(replacerSocket->write(msgBlue.c_str(), static_cast<qint64>(msgBlue.length())) == -1){
                std::cout << "[Example] Failed to write to replacer socket: " << replacerSocket->errorString().toStdString() << std::endl;
            }
            }
            else{
                // Now creating an placement command for the yellow team
                VSSRef::team_to_ref::VSSRef_Placement placementCommandYellow;
                VSSRef::Frame *placementFrameYellow = new VSSRef::Frame();
                placementFrameYellow->set_teamcolor(VSSRef::Color::YELLOW);
                /*for(int x = 0; x < 3; x++){
                    VSSRef::Robot *robot = placementFrameYellow->add_robots();
                    robot->set_robot_id(static_cast<uint32_t>(x));
                    robot->set_x(-0.5);
                    robot->set_y(-0.2 + (0.2 * x));
                    robot->set_orientation(180.0);
                 }*/
            //placementCommandYellow.set_allocated_world(placementFrameYellow);

            // Sending yellow
            std::string msgYellow;
            placementCommandYellow.SerializeToString(&msgYellow);
            if(replacerSocket->write(msgYellow.c_str(), static_cast<qint64>(msgYellow.length())) == -1){
                std::cout << "[Example] Failed to write to replacer socket: " << replacerSocket->errorString().toStdString() << std::endl;
            }
            }
            received = true;
        }

        delete [] buffer; 
        // method which waits and receives a new state from simulator or vision
         if (visionClient.receive(packet)) {
            //printf("-----Received Wrapper Packet---------------------------------------------\n");
            //see if the packet contains a robot detection frame:
            if (packet.has_frame()) {
                state = receiveInterface.receiveState(packet);
                            
     }
        //state = receiveInterface.receiveState();

        for (unsigned int i = 0; i < robots.size(); i++) {
            RodetasRobot &robot = robots[i];

            robot.updateSelfState(state.robots[i]);
            robot.updateState(state);
            robot.calcAction();

            commands[i] = robot.getCommand();

            //debug.finalPoses[i] = robot.getFinalPose();
            //debug.stepPoints[i] = robot.getStepPoint();
            //debug.paths[i] = robot.getPath();
        }

        std::cout<<std::endl;

        coach.manage(robots, state, Config::playersSwap, isFreeBall, positionStatus);

        sendInterface.sendCommands(robots, isPlaying, isTestingTransmission,my_robots_are_yellow);
        //debugInterface.sendDebug(debug);
   
    }
}

if(replacerSocket->isOpen())
        replacerSocket->close();

    if(refereeClient->isOpen())
        refereeClient->close();

    /*if(Config::controlWindow)
        threadWindowControl->detach();*/
}

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
    // Closing sockets  
    exit(0);
}
