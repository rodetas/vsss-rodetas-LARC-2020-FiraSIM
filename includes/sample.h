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
#include <InterfaceCore.h>
#include <FieldTransformation.h>
#include <State.h>
#include <vector>
#include "StateReceiverAdapter.h"

using namespace std;
using namespace common;

class Sample {
private:

    Interface interface_send;

	vss_command::Global_Commands global_commands;

protected:
    bool real_environment;
    string team_color;
    string ip_send_command;

	common::Command commands[3];
    common::Debug debug;

public:
    Sample() = default;

    void init_sample(string, bool);
    void send_commands();
};

#endif // _SAMPLE_H_