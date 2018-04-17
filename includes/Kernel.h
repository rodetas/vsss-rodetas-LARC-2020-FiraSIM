/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <config.h>
#include <sample.h>
#include <transmission.h>
#include <strategies/StrategyBase.h>
#include <strategies/StrategyAttack.h>
#include <strategies/StrategyDefense.h>
#include <strategies/StrategyGoal.h>

#include <RodetasRobot.h>
#include <DebugSenderAdapter.h>
#include <StateReceiverAdapter.h>

using namespace std;
using namespace common;

class Kernel : public Sample {

public:
    Kernel();

	void init();
	void loop();

	void apply();
	void initialize_strategies();
	void initialize_robots();
	void define_function_for_each_robot();

private:
	map<string, int> id;
	map<string, StrategyBase*> strategies;

	Transmission transmission;
    RodetasState state;

	int timeLastChange;
};

#endif // _STRATEGY_H_
