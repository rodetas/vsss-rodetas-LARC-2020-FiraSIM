//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_COMMANDSENDADAPTER_H
#define SDK_RODETAS_COMMANDSENDADAPTER_H

#include <Common.h>

class CommandSendAdapter{

public:

    CommandSendAdapter(string, bool);

    void createSocketSendCommand();
    void sendCommands(vector<common::Command>);

private:

    Interface interfaceSend;
    vss_command::Global_Commands globalCommands;

    bool isRealEnvironment;
    string teamColor;

};

#endif //SDK_RODETAS_COMMANDSENDADAPTER_H
