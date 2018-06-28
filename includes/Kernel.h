/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <RodetasRobot.h>
#include <Window/WindowControl.h>
#include <Communication/DebugSenderAdapter.h>
#include <Communication/StateReceiverAdapter.h>
#include <Communication/CommandSendAdapter.h>
#include <Strategies/RobotStrategyDefender.h>
#include <Strategies/RobotStrategyGoal.h>
#include <RobotStrategyFactory.h>
#include <Config.h>
#include <thread>

using namespace std;
using namespace common;

class Kernel {

public:
    Kernel();

	void loop();

	void updatePlayingState(bool);
	void updateTestingState(bool);
    void freeBallPositions(bool);
    void exitProgram();

private:

	thread* threadWindowControl;

	bool isPlaying;
	bool isTestingTransmission;
    bool isFreeBall;
    bool isRunning;

	WindowControl windowControl;

	void windowThreadWrapper();
};

#endif // _STRATEGY_H_
