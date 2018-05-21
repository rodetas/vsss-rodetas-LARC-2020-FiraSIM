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

    float defineRepulsiveFi(btVector3 robot, btVector3 virtualObstacle);

    float defineFi(RobotState robot, btVector3 robotPosition, btVector3 target, btVector3 arrivalOrientation,
                   std::vector<RobotState> robots);

    float toDomain(float fi);

    btVector3 getS(btVector3 robotSpeed, btVector3 obstacleSpeed);

    btVector3 getVirtualPosition(btVector3 robot, btVector3 obstacle, btVector3 s);

private:

    float n;
    float k0;
    float dmin;
    float delta;
};

#endif //SDK_RODETAS_UNIVECTORFIELD_H
