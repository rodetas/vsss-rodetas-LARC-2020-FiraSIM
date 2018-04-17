//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_STATERECEIVERADAPTER_H
#define SDK_RODETAS_STATERECEIVERADAPTER_H

#include <common.h>
#include <RodetasState.h>
#include <InterfaceCore.h>
#include <State.h>
#include <MathHelper.h>

class StateReceiverAdapter {

public:

    StateReceiverAdapter();

    void createSocketReceiveState();
    RodetasState receiveState(bool change_side, string main_color);

private:
    vss::InterfaceCore interface_receive;

};


#endif //SDK_RODETAS_STATERECEIVERADAPTER_H