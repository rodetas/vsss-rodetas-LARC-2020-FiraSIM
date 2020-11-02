//
// Created by manoel on 23/04/18.
//

#ifndef SDK_RODETAS_COMMANDSENDADAPTER_H
#define SDK_RODETAS_COMMANDSENDADAPTER_H

#include <Domain/TeamType.h>
#include <RodetasRobot.h>
#include <Communication/Transmission.h>
#include <Communications/CommandSender.h>
#include <QtCore>
#include <QtNetwork>
#include "../net/robocup_ssl_client.h"
#include "../net/grSim_client.h"
#include "../net/pb/command.pb.h"
#include "../net/pb/common.pb.h"
#include "../net/pb/packet.pb.h"
#include "../net/pb/replacement.pb.h"

class CommandSendAdapter{

public:

    CommandSendAdapter(vss::TeamType, bool);

    void createSocketSendCommand();
    void sendCommands(std::vector<RodetasRobot>, bool, bool, bool);

private:

    vss::CommandSender interfaceSend;

    bool isRealEnvironment;
    vss::TeamType teamColor;

    Transmission transmission;

};

#endif //SDK_RODETAS_COMMANDSENDADAPTER_H
