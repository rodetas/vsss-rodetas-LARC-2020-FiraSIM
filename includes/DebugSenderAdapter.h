//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_DEBUGSENDERADAPTER_H
#define SDK_RODETAS_DEBUGSENDERADAPTER_H

#include <interface.h>
#include <Common.h>
#include <Config.h>
#include <TeamColor.h>

class DebugSendAdapter {

public:

    DebugSendAdapter(TeamColor::Color teamColor, bool isDebug);

    //! initialize socket parameters
    void createSocketDebug();

    //! sends debug packet
    void sendDebug(common::Debug debug);

private:
    Interface interfaceDebug;
    vss_debug::Global_Debug globalDebug;

    TeamColor::Color teamColor;
    bool isDebug;

};

#endif //SDK_RODETAS_DEBUGSENDERADAPTER_H
