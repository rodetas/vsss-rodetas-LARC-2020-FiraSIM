#include <config.h>

int    Config::argc;
char** Config::argv;
bool   Config::debug;
bool   Config::real_environment;
string Config::name;
string Config::side_team;
string Config::color_team;
string Config::ip_send_debug;
string Config::ip_send_command;
string Config::ip_receive_state;

void Config::init(int _argc, char** _argv) {
    argc = _argc;
    argv = _argv;

    debug = false;
    real_environment = false;
    side_team = "left";

    argument_parse();
}

void Config::argument_parse() {
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
        ("debug,d", "(Optional) open the debug rotine")
        ("name,n", bpo::value<std::string>()->default_value("sample"), "(Optional) Specify the name of the strategy.")
        ("ip_receive_state,i", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Vision.")
        ("ip_send_debug,I", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Viewer.")
        ("ip_send_command,s", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Simulator.")
        ("color,c", bpo::value<std::string>()->default_value(" "), "(Required) Specify the main color of your team, may be yellow or blue.");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
    }

    if (vm.count("debug")){
        debug = true;
    }

    name = vm["name"].as<string>();
    color_team = vm["color"].as<string>();
    ip_send_debug = vm["ip_send_debug"].as<string>();
    ip_send_command = vm["ip_send_command"].as<string>();
    ip_receive_state = vm["ip_receive_state"].as<string>();
}

bool Config::ready_param() {
    if (color_team == " ") {
        cout << "ERROR: You must set a color to your team." << endl;
        return true;
    }
    return false;
}