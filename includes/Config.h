#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <boost/program_options.hpp>
//#include <iostream>
//#include <string>
#include <Domain/FieldTransformationType.h>
#include <Domain/TeamType.h>
#include <Domain/Point.h>

namespace bpo = boost::program_options;

class Config {

public:
    static bool debug;
    static bool realEnvironment;
    static bool controlWindow;
    static vss::FieldTransformationType changeSide;
	static vss::TeamType teamColor;
	static bool playersSwap;
	static std::string xbeePort;

	static vss::Point goalSize;
	static vss::Point goalAreaSize;

    static bool argumentParse(int ,char**);

};
#endif // _CONFIG_H_
