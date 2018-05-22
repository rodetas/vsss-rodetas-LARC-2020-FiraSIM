/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Boost.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Common.h"

using namespace std;

class Config{

public:
    static bool debug;
    static bool realEnvironment;
    static bool changeSide;
    static bool playersSwap;
	static string test;
    static string teamColor;

	static common::btVector3 fieldSize;
	static common::btVector3 goalSize;
	static common::btVector3 goalAreaSize;

    static bool argumentParse(int ,char**);

};
#endif // _CONFIG_H_
