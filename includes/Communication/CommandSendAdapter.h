//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_COMMANDSENDADAPTER_H
#define SDK_RODETAS_COMMANDSENDADAPTER_H

#include <Common.h>
#include <Domain/TeamType.h>
#include <Communication/Transmission.h>

class CommandSendAdapter{

public:

    CommandSendAdapter(vss::TeamType, bool);

    void createSocketSendCommand();
    void sendCommands(vector<common::Command>);

private:

    Interface interfaceSend;
    vss_command::Global_Commands globalCommands;

    bool isRealEnvironment;
    vss::TeamType teamColor;

    Transmission transmission;

};

#endif //SDK_RODETAS_COMMANDSENDADAPTER_H
