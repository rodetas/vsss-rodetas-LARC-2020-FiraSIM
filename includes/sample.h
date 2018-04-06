/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include <common.h>
#include <interface.h>
#include <vector>
#include <state.h>

using namespace std;
using namespace common;

class Sample{
private:
    Interface interface_receive;
    Interface interface_send;
    Interface interface_debug;

    vss_state::Global_State global_state;
	vss_command::Global_Commands global_commands;
	vss_debug::Global_Debug global_debug;

protected:
    int situation;
    int flag_init;
    bool is_debug;
    bool real_environment;
    string team_color;
    string ip_send_debug;
    string ip_send_command;
    string ip_receive_state;

    State state;
	common::Command commands[3];
    common::Debug debug;

public:
    Sample() = default;

    void init_sample(string, bool, bool);
    void receive_state();
    void send_commands();
    void send_debug();
};

#endif // _SAMPLE_H_