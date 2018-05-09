#include <Config.h>

bool Config::debug = false;
bool Config::realEnvironment = false;
bool Config::changeSide = false;
string Config::teamColor;

bool Config::argumentParse(int argc, char** argv) {
    namespace bpo = boost::program_options;
  
    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) print this help message")
        ("debug,d", "(Optional) enables the debug rotine")
        ("environment,e", "(Optional) set real environment")
        ("side,s", bpo::value<std::string>()->default_value("left"), "(Optional) Specify the team's side;")
        ("color,c", bpo::value<std::string>()->default_value("blue"), "(Optional) Specify the main color of your team, may be yellow or blue.");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
        return false;
    }

    if (vm["side"].as<string>() == "right"){
        changeSide = true;
    }

    debug = (bool) vm.count("debug");
    realEnvironment = (bool) vm.count("environment");

    //@TODO: transformar cor de string para enum
    teamColor = vm["color"].as<string>();

    return true;
}
