#include <config.h>

bool Config::debug = false;
bool Config::real_environment = false;
string Config::team_side;
string Config::team_color;

void Config::argument_parse(int argc, char** argv) {
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
        ("debug,d", "(Optional) open the debug rotine")
        ("environment,e", "(Optional) set real environment")
        ("side,s", bpo::value<std::string>()->default_value(" "), "(Required) Specify the team's side;")
        ("color,c", bpo::value<std::string>()->default_value(" "), "(Required) Specify the main color of your team, may be yellow or blue.");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
    }

    debug = vm.count("debug");
    real_environment = vm.count("environment");

    team_side = vm["side"].as<string>();
    team_color = vm["color"].as<string>();
}

bool Config::ready_param() {
    if (team_color == "yellow" || team_color == "blue") {
        return true;
    }
    cout << "ERROR: You must set a color to your team." << endl;
    return false;
}