#include <config.h>

bool Config::debug = false;
bool Config::real_environment = false;
bool Config::change_side = false;
string Config::team_color;

bool Config::argument_parse(int argc, char** argv) {
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
        change_side = true;
    }

    debug = (bool) vm.count("debug");
    real_environment = (bool) vm.count("environment");

    //@TODO: transformar cor de string para enum
    team_color = vm["color"].as<string>();

    return true;
}