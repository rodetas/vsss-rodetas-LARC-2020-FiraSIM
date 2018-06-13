//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_COMMANDSENDADAPTER_H
#define SDK_RODETAS_COMMANDSENDADAPTER_H

#include <Common.h>
#include <TeamColor.h>

class CommandSendAdapter{

public:

    CommandSendAdapter(TeamColor::Color, bool);

    void createSocketSendCommand();
    void sendCommands(vector<common::Command>);

private:

    Interface interfaceSend;
    vss_command::Global_Commands globalCommands;

    bool isRealEnvironment;
    TeamColor::Color teamColor;

};

#endif //SDK_RODETAS_COMMANDSENDADAPTER_H
