/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <boost/program_options.hpp>

#include <sstream>
#include <iostream>
#include <string>
#include <Domain/FieldTransformationType.h>
#include <Domain/TeamType.h>
#include "Common.h"

using namespace std;
namespace bpo = boost::program_options;

class Config{

public:
    static bool debug;
    static bool realEnvironment;
    static bool controlWindow;
    static vss::FieldTransformationType changeSide;
	static vss::TeamType teamColor;
	static bool playersSwap;

	static vss::Point fieldSize;
	static vss::Point goalSize;
	static vss::Point goalAreaSize;

    static bool argumentParse(int ,char**);

};
#endif // _CONFIG_H_
