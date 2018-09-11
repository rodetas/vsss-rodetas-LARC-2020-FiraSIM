//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_ROBOTPOSITIONING_H
#define SDK_RODETAS_ROBOTPOSITIONING_H

#include <Movements/UnivectorField.h>
#include <Movements/Movimentation.h>
#include <Agent.h>

class RobotPositioning : public Agent {

public:

    vss::WheelsCommand applyStrategy(RobotState, RodetasState, RobotStrategyBase) override;

    // este metodo DEVE ser implementado em toda classe filha
    vss::Pose defineTargetAndArrivalOrientation() override = 0;

    float applyUnivectorField(vss::Pose) override;

    // este metodo DEVE ser implementado em toda classe filha
    virtual vss::WheelsCommand specificStrategy(vss::WheelsCommand) = 0;

private:
    Movimentation movimentation;

};

#endif //SDK_RODETAS_ROBOTPOSITIONING_H
