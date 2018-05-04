/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <boost.h>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class Config{

public:
    static bool debug;
    static bool realEnvironment;
    static bool changeSide;
    static string teamColor;

    static bool argumentParse(int ,char**);
};
#endif // _CONFIG_H_