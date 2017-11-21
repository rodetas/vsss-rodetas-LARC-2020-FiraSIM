/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "sample.h"
#include "strategies/StrategyBase.h"
#include "strategies/StrategyAttack.h"
#include "strategies/StrategyDefense.h"
#include "strategies/StrategyGoal.h"

using namespace std;
using namespace common;

class Strategy : public Sample{
	/*
		Sample :: string main_color;
		Sample :: bool is_debug;
		Sample :: bool real_environment;
		Sample :: int situation;

		Sample :: common::State state;
		Sample :: common::Command commands[3];
		Sample :: common::Debug debug;
	*/
protected:
	float robot_radius;
	float distance_to_stop;

	btVector3 final;
	bool changePose;

	map<string, Robot*> team;
	map<string, StrategyBase*> strategies;

public:
	Strategy();	

	void init(string main_color, bool is_debug, bool real_environment, string ip_receive_state, string ip_send_debug, string ip_send_command, string name);
	void loop();

	void initialize_strategies();
    void initialize_robots();
	void convert_receive_state();
	void convert_send_commands();
};

#endif // _STRATEGY_H_