//
// Created by paulo on 19/05/18.
//

/* This code is based on two articles about Univector Field. The first is
 * "Evolutionary Programming-Based Univector Field Navigation Method for Fast Mobile Robots" and we use from
 * this article only the Univector Field to move the robot to a target with a desire arrival orientation. The second article is
 * "Evolutionary Univector Field-based Navigation with Collision Avoidance for Mobile Robot" and we use from this article only
 * the collision avoidance part. The mixture of these two articles creates the most powerful Rodetas's movimentation until now, May 2018.
 */

#ifndef SDK_RODETAS_UNIVECTORFIELD_H
#define SDK_RODETAS_UNIVECTORFIELD_H

#include <RobotState.h>
#include <RodetasState.h>
#include <Common.h>

class UnivectorField {
public:

    UnivectorField(float n, float k0, float dmin, float delta);

    UnivectorField();

    //Defines the univector field angle with obstacles, the vector "obstacles" contains the position and the velocity of the obstacles
    float defineFi(RobotState robot, btVector3 target, btVector3 arrivalOrientation,
                   vector<pair<btVector3, btVector3>> obstacles);

    //Draws the path to the target with obstacles
    Path drawPath(RobotState robot, btVector3 target, btVector3 arrivalOrientation,
                  vector<pair<btVector3, btVector3>> obstacles);

private:

    //This constant defines the robot curve
    float n;
    //This constant adjusts the creation of the virtual position of the obstacles with its velocity
    float k0;
    //Defines the radius that the robot will suffer only repulsive angle
    float dmin;
    //This constant is used in the gaussian function
    float delta;


    //Calculates only the move angle "fi" to move to the target with a desire arrival orientation. From the first article
    float defineMoveFi(btVector3 robot, btVector3 target, btVector3 arrivalOrientation);

    //Calculates only the repulsive angle "fi" to escape from the obstacle
    float defineRepulsiveFi(btVector3 robot, btVector3 virtualObstacle);

    //Calculates the "s". S is a vector that is used for the creation of the virtual obstacle
    btVector3 getS(btVector3 robotSpeed, btVector3 obstacleSpeed);

    //Creates the virtual position of the obstacle based on its velocity
    btVector3 getVirtualPosition(btVector3 robot, btVector3 obstacle, btVector3 s);

    //Keeps the angle in the domain [-PI, PI]
    float toDomain(float fi);
};

#endif //SDK_RODETAS_UNIVECTORFIELD_H
