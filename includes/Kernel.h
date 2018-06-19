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
#include <WindowControl.h>
#include <Communication/DebugSenderAdapter.h>
#include <Communication/StateReceiverAdapter.h>
#include <Communication/CommandSendAdapter.h>
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

private:

	thread* threadWindowControl;

	bool isPlaying;
	bool isTestingTransmission;

	WindowControl windowControl;

	void windowThreadWrapper();
};

#endif // _STRATEGY_H_
