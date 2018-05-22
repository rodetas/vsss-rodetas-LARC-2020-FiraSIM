#include <Config.h>

bool Config::debug = false;
bool Config::realEnvironment = false;
bool Config::changeSide = false;
bool Config::playersSwap = true;
string Config::teamColor;
string Config::test;

common::btVector3 Config::fieldSize = {150,130};
common::btVector3 Config::goalSize = {10, 40};
common::btVector3 Config::goalAreaSize = common::btVector3(fieldSize.x*0.2, fieldSize.y*0.6);

bool Config::argumentParse(int argc, char** argv) {
    namespace bpo = boost::program_options;
  
    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) print this help message")
        ("debug,d", "(Optional) enables the debug rotine")
        ("environment,e", "(Optional) set real environment")
        ("rotate,r", "(Optional) rotate robots positions")
		("swap,s", "(Optional) Turn off player's swap.") 
        ("color,c", bpo::value<std::string>()->default_value("blue"), "(Optional) Specify the main color of your team, may be yellow or blue.");
		//("tests,t", bpo::value<std::string>()->default_value("t1"), "(Optional) Specify the test you want to do: t1- generateMessage test; t2- checkSum test.");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
        return false;
    }
    
   
    playersSwap = (bool) vm.count("swap");
    changeSide = (bool) vm.count("rotate");
    debug = (bool) vm.count("debug");
    realEnvironment = (bool) vm.count("environment");

    //@TODO: transformar cor de string para enum
    teamColor = vm["color"].as<string>();
	//	test= vm["tests"].as<string>();

    return true;
}
