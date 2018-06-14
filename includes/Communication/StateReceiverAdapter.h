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
#include <Domain/FieldTransformationType.h>
#include <Domain/TeamType.h>

class StateReceiverAdapter {

public:

    StateReceiverAdapter(vss::TeamType, vss::FieldTransformationType);

    void createSocketReceiveState();
    RodetasState receiveState();

private:
    vss::FieldTransformationType changeSide;
    vss::TeamType teamColor;

    vss::StateReceiver stateReceiver;

};


#endif //SDK_RODETAS_STATERECEIVERADAPTER_H
