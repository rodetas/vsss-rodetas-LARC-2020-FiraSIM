#include <Config.h>

bool Config::debug = false;
bool Config::realEnvironment = false;
vss::FieldTransformationType Config::changeSide = vss::FieldTransformationType::None;
vss::TeamType Config::teamColor = vss::TeamType::Blue;
bool Config::playersSwap = true;


common::btVector3 Config::fieldSize = {170,130};
common::btVector3 Config::goalSize = {10, 40};
common::btVector3 Config::goalAreaSize = common::btVector3(fieldSize.x*0.1, fieldSize.y*0.6);

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
	
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
        return false;
    }
    
   
    playersSwap = !(bool) vm.count("swap");
    changeSide = (vss::FieldTransformationType) vm.count("rotate");
    debug = (bool) vm.count("debug");
    realEnvironment = (bool) vm.count("environment");

    string color = vm["color"].as<string>();
    if(color == "yellow"){
        teamColor = vss::TeamType::Yellow;
    }

    return true;
}
