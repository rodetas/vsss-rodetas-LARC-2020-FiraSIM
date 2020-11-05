#include <Config.h>
#include <Domain/Constants.h>

bool Config::debug = false;
bool Config::realEnvironment = false;
bool Config::controlWindow = false;
vss::FieldTransformationType Config::changeSide = vss::FieldTransformationType::None;
vss::TeamType Config::teamColor = vss::TeamType::Blue;
bool Config::playersSwap = true;
std::string Config::xbeePort = "0";
vss::Point Config::goalSize = {0.1, 0.4};
vss::Point Config::fieldSize = {1.5, 1.3};
vss::Point Config::goalAreaSize = vss::Point((vss::MAX_COORDINATE_X  - 20)*0.1, vss::MAX_COORDINATE_Y*0.539);

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
		("window,w", "(Optional) show control's window")
		("xbeePort,x", bpo::value<std::string>()->default_value("0"), "(Optional) specify xbee usb port (ex: 0 or 1)")
        ("color,c", bpo::value<std::string>()->default_value("blue"), "(Optional) Specify the main color of your team, may be yellow or blue.");


    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        std::cout << desc << std::endl;
        return false;
    }

    playersSwap = !(bool) vm.count("swap");
    changeSide = (vss::FieldTransformationType) vm.count("rotate");
    debug = (bool) vm.count("debug");
    realEnvironment = (bool) vm.count("environment");
    controlWindow = realEnvironment or (bool) vm.count("window");
    xbeePort = vm["xbeePort"].as<std::string>();

    std::string color = vm["color"].as<std::string>();
    if(color == "yellow"){
        teamColor = vss::TeamType::Yellow;
    }

    return true;
}
