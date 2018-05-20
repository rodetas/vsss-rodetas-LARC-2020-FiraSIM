//
// Created by paulo on 19/05/18.
//

#include <UnivectorField.h>

UnivectorField::UnivectorField(float n, float k0, float dmin, float delta) : n(n), k0(k0), dmin(dmin), delta(delta){}

UnivectorField::UnivectorField() {}

float UnivectorField::defineMoveFi(btVector3 robot, btVector3 target, btVector3 arrivalOrientation){

    float pr = atan2((arrivalOrientation.y - robot.y),(arrivalOrientation.x-robot.x));
    float pg = atan2((target.y - robot.y),(target.x-robot.x));

    float alpha = pr - pg;
    float fi = pg - n*alpha;
    return fi;
}
