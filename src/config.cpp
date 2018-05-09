#include <config.h>

bool Config::debug = false;
bool Config::realEnvironment = false;
bool Config::changeSide = false;
string Config::teamColor;
btVector3 Config::fieldSize = {150,130};
btVector3 Config::image = {150,130};

void Config::argument_parse(int argc, char** argv) {
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
        ("debug,d", "(Optional) open the debug rotine")
        ("environment,e", "(Optional) set real environment")
        ("side,s", bpo::value<std::string>()->default_value("left"), "(Required) Specify the team's side;")
        ("color,c", bpo::value<std::string>()->default_value(" "), "(Required) Specify the main color of your team, may be yellow or blue.");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
    }

    //@TODO passar left ou right mas manter default value como left
    if (vm["side"].as<string>() == "right"){
        changeSide = true;
    }

    debug = vm.count("debug");
    realEnvironment = vm.count("environment");

//@TODO: deixar valor padrao para cor
    teamColor = vm["color"].as<string>();
}

bool Config::ready_param() {
    if (teamColor == "yellow" || teamColor == "blue") {
        return true;
    }
    cout << "ERROR: You must set a color to your team." << endl;
    return false;
}