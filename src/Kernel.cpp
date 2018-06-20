#include <Kernel.h>

Kernel::Kernel() = default;

void Kernel::loop() {

    if(Config::controlWindow)
        threadWindowControl = new thread(std::bind(&Kernel::windowThreadWrapper, this));

    RobotStrategyFactory coach;

    StateReceiverAdapter receiveInterface(Config::teamColor, Config::changeSide);
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);

    vector<RodetasRobot> robots;
    vector<vss::WheelsCommand> commands(3);

    for (unsigned int i = 0; i < 3; i++) robots.emplace_back(RodetasRobot(i, (MindSet) i));

    RodetasState state;

    vss::Debug debug;
    debug.paths.resize(3);
    debug.finalPoses.resize(3);
    debug.stepPoints.resize(3);

    robots[0].setStrategy(new RobotStrategyAttack());
    robots[1].setStrategy(new RobotStrategyDefender());
    robots[2].setStrategy(new RobotStrategyGoal());

    while (true) {

        // method which waits and receives a new state from simulator or vision
        state = receiveInterface.receiveState();

        for (unsigned int i = 0; i < robots.size(); i++) {
            RodetasRobot &robot = robots[i];

            robot.updateSelfState(state.robots[i]);
            robot.updateState(state);
            robot.calcAction();

            commands[i] = robot.getCommand();

            debug.finalPoses[i] = robot.getFinalPose();
            debug.stepPoints[i] = robot.getStepPoint();
            debug.paths[i] = robot.getPath();
        }

        coach.manage(robots, state, Config::playersSwap);

        sendInterface.sendCommands(commands, isPlaying, isTestingTransmission);
        debugInterface.sendDebug(debug);
    }
}

void Kernel::windowThreadWrapper() {

    windowControl.signalUpdatePlaying.connect(sigc::mem_fun(this, &Kernel::updatePlayingState));
    windowControl.signalUpdateTesting.connect(sigc::mem_fun(this, &Kernel::updateTestingState));

    windowControl.start();
}

void Kernel::updatePlayingState(bool playing) {
    this->isPlaying = playing;
}

void Kernel::updateTestingState(bool testing) {
    this->isTestingTransmission = testing;
}