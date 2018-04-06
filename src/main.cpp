/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "config.h"
#include <strategy.h>

int main(int argc, char** argv){
	
    Config::init(argc, argv);

    if (Config::ready_param()){
        //Strategy strategy;
        //strategy.init(color, debug, false, ip_receive_state, ip_send_debug, ip_send_command, name);
    }

	return 0;
}