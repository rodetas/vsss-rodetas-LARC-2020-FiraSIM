//
// Created by manoel on 17/04/18.
//

#ifndef SDK_RODETAS_ROBOTSTRATEGY_H
#define SDK_RODETAS_ROBOTSTRATEGY_H

#include <Domain/RobotState.h>
#include <Domain/RodetasState.h>
#include <Domain/RobotSpeed.h>
#include <Domain/Pose.h>
#include <Domain/Path.h>
#include <Domain/Constants.h>
#include <Helpers/Math.h>
#include <Strategies/RobotStrategyBase.h>
#include <Movements/Movimentation.h>
#include <Movements/UnivectorField.h>
#include <Agent.h>
#include <Config.h>

class RobotStrategy : public Agent {

public:
    RobotStrategy();



    vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase) override;

    vss::Pose defineTarget() override = 0;

    float applyUnivectorField(vss::Pose) override = 0;

    virtual vss::WheelsCommand specificStrategy(vss::WheelsCommand) = 0;

    //@TODO: inserir comentarios em cada estrategia
    virtual vss::WheelsCommand cornerStrategy(vss::WheelsCommand);

    virtual vss::WheelsCommand stopStrategy(vss::WheelsCommand);

    virtual vss::WheelsCommand blockedStrategy(vss::WheelsCommand);

    virtual vss::WheelsCommand kickStrategy(vss::WheelsCommand);

protected:
    Movimentation movimentation;

};

#endif //SDK_RODETAS_ROBOTSTRATEGY_H
