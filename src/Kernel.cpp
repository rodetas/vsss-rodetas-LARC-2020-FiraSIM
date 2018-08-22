#include <Kernel.h>

Kernel::Kernel() {
    isPlaying = false;
    isTestingTransmission = false;
    isFreeBall = false;
    isRunning = true;
};

void Kernel::loop() {

    if(Config::controlWindow)
        threadWindowControl = new thread(std::bind(&Kernel::windowThreadWrapper, this));

    RobotStrategyFactory coach;

    StateReceiverAdapter receiveInterface(Config::teamColor, Config::changeSide);
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);

    vector<RodetasRobot> robots;
    robots.emplace_back(RodetasRobot(0, MindSet::Attacker, new RobotStrategyAttack()));
    robots.emplace_back(RodetasRobot(1, MindSet::Defender, new RobotStrategyDefenderBack()));
    robots.emplace_back(RodetasRobot(2, MindSet::GoalKeeper, new RobotStrategyGoal()));

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
            robot.updateState(state);
            robot.calcAction();

            commands[i] = robot.getCommand();

            //debug.finalPoses[i] = robot.getFinalPose();
            debug.stepPoints[i] = robot.getStepPoint();
            debug.paths[i] = robot.getPath();
        }

        coach.manage(robots, state, Config::playersSwap, isFreeBall);

        sendInterface.sendCommands(commands, isPlaying, isTestingTransmission);
        debugInterface.sendDebug(debug);
    }

    if(Config::controlWindow)
        threadWindowControl->detach();
}

void Kernel::windowThreadWrapper() {

    windowControl.signalUpdatePlaying.connect(sigc::mem_fun(this, &Kernel::updatePlayingState));
    windowControl.signalUpdateTesting.connect(sigc::mem_fun(this, &Kernel::updateTestingState));
    windowControl.signalChangeFunction.connect(sigc::mem_fun(this, &Kernel::freeBallPositions));
    windowControl.signalCloseWindow.connect(sigc::mem_fun(this, &Kernel::exitProgram));

    windowControl.start();
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
