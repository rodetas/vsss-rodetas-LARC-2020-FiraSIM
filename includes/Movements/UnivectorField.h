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

#include <Domain/RobotState.h>
#include <Domain/RodetasState.h>
#include <Domain/Path.h>
#include <Domain/Pose.h>
#include <vector>

class UnivectorField {
public:

    UnivectorField();

    void setUnivectorWithoutCurves();

    void setUnivectorWithCurves();

    //Defines the univector field angle with obstacles, the vector "obstacles" contains the position and the velocity of the obstacles
    float defineFi(RobotState robot, vss::Pose target, std::vector<std::pair<vss::Point, vss::Point>> obstacles);

    //Draws the path to the target with obstacles
    vss::Path drawPath(RobotState robot, vss::Pose target, std::vector<std::pair<vss::Point, vss::Point>> obstacles);

private:

    //This constant defines the robot curve
    float n;
    //This constant defines also the robot curve. It is the distance between the target and the point that defines the arrival orientation
    float orientationDistance;
    //This constant adjusts the creation of the virtual position of the obstacles with its velocity
    float k0;
    //Defines the radius that the robot will suffer only repulsive angle
    float dmin;
    //This constant is used in the gaussian function
    float delta;


    //Calculates only the move angle "fi" to move to the target with a desire arrival orientation. From the first article
    float defineMoveFi(vss::Point robot, vss::Pose target, vss::Point arrivalOrientation);

    //Calculates only the repulsive angle "fi" to escape from the obstacle
    float defineRepulsiveFi(vss::Point robot, vss::Point virtualObstacle);

    //Calculates the "s". S is a vector that is used for the creation of the virtual obstacle
    vss::Point getS(vss::Point robotSpeed, vss::Point obstacleSpeed);

    //Creates the virtual position of the obstacle based on its velocity
    vss::Point getVirtualPosition(vss::Point robot, vss::Point obstacle, vss::Point s);

    //Calculates the arrival Orientation Point from an arrival Angle (0 - 2PI) from the target
    vss::Point getArrivalPoint(vss::Pose target);
};

#endif //SDK_RODETAS_UNIVECTORFIELD_H
