//
// Created by paulo on 19/05/18.
//

#ifndef SDK_RODETAS_UNIVECTORFIELD_H
#define SDK_RODETAS_UNIVECTORFIELD_H

#include <RobotState.h>
#include <RodetasState.h>
#include <Common.h>

class UnivectorField {
public:

    UnivectorField(float n, float k0, float dmin, float delta);

    UnivectorField();

    float defineFi(RobotState robot, btVector3 target, btVector3 arrivalOrientation,
                   vector<pair<btVector3, btVector3>> obstacles);

    Path drawPath(RobotState robot, btVector3 target, btVector3 arrivalOrientation,
                  vector<pair<btVector3, btVector3>> obstacles);

private:

    float n;
    float k0;
    float dmin;
    float delta;

    float toDomain(float fi);

    btVector3 getS(btVector3 robotSpeed, btVector3 obstacleSpeed);

    btVector3 getVirtualPosition(btVector3 robot, btVector3 obstacle, btVector3 s);

    float defineMoveFi(btVector3 robot, btVector3 target, btVector3 arrivalOrientation);

    float defineRepulsiveFi(btVector3 robot, btVector3 virtualObstacle);
};

#endif //SDK_RODETAS_UNIVECTORFIELD_H
