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
#include <DebugSenderAdapter.h>
#include <StateReceiverAdapter.h>
#include <CommandSendAdapter.h>
#include <WindowControl.h>
#include <Config.h>
#include <thread>

using namespace std;
using namespace common;

class Kernel {

public:
    Kernel();

	void loop();

private:

	thread* threadWindowControl;

	bool isPlaying;
	bool isTestingTransmission;

	WindowControl windowControl;

	void windowThreadWrapper();
};

#endif // _STRATEGY_H_
