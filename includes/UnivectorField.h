//
// Created by paulo on 19/05/18.
//

#ifndef SDK_RODETAS_UNIVECTORFIELD_H
#define SDK_RODETAS_UNIVECTORFIELD_H

#include <RobotState.h>
#include <RodetasState.h>

class UnivectorField {
public:

    UnivectorField(float n, float k0, float dmin, float delta);
    UnivectorField();

    float defineMoveFi(btVector3 robot, btVector3 target, btVector3 arrivalOrientation);

private:

    float n;
    float k0;
    float dmin;
    float delta;
};
#endif //SDK_RODETAS_UNIVECTORFIELD_H
