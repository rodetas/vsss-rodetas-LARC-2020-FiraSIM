//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_STATERECEIVERADAPTER_H
#define SDK_RODETAS_STATERECEIVERADAPTER_H

#include <Common.h>
#include <RodetasState.h>
#include <Communications/StateReceiver.h>
#include <Domain/State.h>
#include <MathHelper.h>
#include <TeamColor.h>
#include <Domain/FieldTransformationType.h>

class StateReceiverAdapter {

public:

    StateReceiverAdapter(string, bool);

    void createSocketReceiveState();
    RodetasState receiveState(bool changeSide, TeamColor::Color mainColor);

private:
    bool changeSide;
    string teamColor;

    vss::StateReceiver stateReceiver;

};


#endif //SDK_RODETAS_STATERECEIVERADAPTER_H
