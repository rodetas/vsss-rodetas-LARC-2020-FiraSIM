#include <Kernel.h>
#include <strategies/RobotStrategyDefender.h>
#include <strategies/RobotStrategyGoal.h>
#include <RobotStrategyFactory.h>
#include <Config.h>

Kernel::Kernel(){
}

void Kernel::loop() {

    RobotStrategyFactory coach;

    StateReceiverAdapter receiveInterface(Config::teamColor, Config::changeSide);
    DebugSendAdapter debugInterface(Config::teamColor, Config::debug);
    CommandSendAdapter sendInterface(Config::teamColor, Config::realEnvironment);

    vector<RodetasRobot> robots;
    vector<Command> commands(3);

    for (unsigned int i = 0; i < 3; i++) robots.emplace_back(RodetasRobot(i, (MindSet) i));

    RodetasState state;

    vss::Debug debug;
    debug.paths.resize(3);
    debug.finalPoses.resize(3);

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
            debug.paths[i] = robot.getPath();
        }

        coach.manage(robots, state, Config::playersSwap);

        sendInterface.sendCommands(commands);
        debugInterface.sendDebug(debug);
    }
}
