//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_COMMANDSENDADAPTER_H
#define SDK_RODETAS_COMMANDSENDADAPTER_H

#include <Common.h>
#include <Domain/TeamType.h>
#include <Communication/Transmission.h>
#include <Communications/CommandSender.h>

class CommandSendAdapter{

public:

    CommandSendAdapter(vss::TeamType, bool);

    void createSocketSendCommand();
    void sendCommands(vector<common::Command>);

private:

    vss::CommandSender interfaceSend;

    bool isRealEnvironment;
    vss::TeamType teamColor;

    Transmission transmission;

    vss::WheelsCommand commandToWheelsCommand(int, Command);

};

#endif //SDK_RODETAS_COMMANDSENDADAPTER_H
