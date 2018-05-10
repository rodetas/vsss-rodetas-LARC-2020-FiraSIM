#include <Kernel.h>
#include <strategies/RobotStrategyDefender.h>
#include <strategies/RobotStrategyGoal.h>
#include <RobotStrategyFactory.h>

Kernel::Kernel(){
	srand(time(NULL));
}

void Kernel::loop() {

    RobotStrategyFactory coach;

    StateReceiverAdapter receiveInterface;
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
        //@TODO jogar parametros para o construtor da classe StateReceiveAdapter
        state = receiveInterface.receiveState(Config::changeSide, Config::teamColor);

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

        coach.manage(robots, state);

        sendInterface.sendCommands(commands);
        debugInterface.sendDebug(debug);
    }
}