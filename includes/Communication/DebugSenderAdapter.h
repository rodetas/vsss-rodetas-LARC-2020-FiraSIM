//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_DEBUGSENDERADAPTER_H
#define SDK_RODETAS_DEBUGSENDERADAPTER_H

#include <Common.h>
#include <Config.h>
#include <Domain/TeamType.h>
#include <Domain/Debug.h>
#include <Communications/DebugSender.h>

class DebugSendAdapter {

public:

    DebugSendAdapter(vss::TeamType teamColor, bool isDebug);

    //! initialize socket parameters
    void createSocketDebug();

    //! sends debug packet
    void sendDebug(vss::Debug debug);

private:

    vss::DebugSender interfaceDebug;

    vss::TeamType teamColor;
    bool isDebug;

};

#endif //SDK_RODETAS_DEBUGSENDERADAPTER_H
