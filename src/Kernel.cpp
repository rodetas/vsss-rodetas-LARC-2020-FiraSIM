#include <Kernel.h>
#include <strategies/RobotStrategyDefender.h>
#include <strategies/RobotStrategyGoal.h>
#include <RobotStrategyFactory.h>
#include <Config.h>

Kernel::Kernel(){
	srand(time(NULL));
}

void Kernel::loop() {

    threadWindowControl = new thread(std::bind(&Kernel::windowThreadWrapper, this));

    RobotStrategyFactory coach;

    StateReceiverAdapter receiveInterface(Config::teamColor, Config::changeSide);
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);

    vector<RodetasRobot> robots;
    vector<Command> commands(3);

    for (unsigned int i = 0; i < 3; i++) robots.emplace_back(RodetasRobot(i, (MindSet) i));

    RodetasState state;
    Debug debug;

    robots[2].setStrategy(new RobotStrategyAttack());
    robots[1].setStrategy(new RobotStrategyDefender());
    robots[0].setStrategy(new RobotStrategyGoal());

    while (true) {

        // method which waits and receives a new state from simulator or vision
        state = receiveInterface.receiveState();

        for (unsigned int i = 0; i < robots.size(); i++) {
            RodetasRobot &robot = robots[i];

            robot.updateSelfState(state.robots[i]);
            robot.updateState(state);
            robot.calcAction();

            commands[i] = robot.getCommand();

            debug.robotsFinalPose[i] = robot.getRobotDebug().robotFinalPose;
            debug.robotsStepPose[i] = robot.getRobotDebug().robotStepPose;
            debug.robotsPath[i] = robot.getRobotDebug().path;

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