//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MATHHELPER_H
#define SDK_RODETAS_MATHHELPER_H

#include <Common.h>

using namespace common;

class Math {

public:
    //! Estimate distance between a set of points.
    static double distancePoint(btVector3, btVector3);

    //! Estimate angle between two straight lines.
    static double angulation(btVector3, btVector3);

    //! Estimate angle between two straight lines in radian.
    static double radian(btVector3, btVector3);

    static double calculateLinearSpeed(double, double);

    //! Given a initial point and two velocities returns the initial point projection considering these two velocities
    static btVector3 calculateProjection(btVector3, double, double);

    //! Transforms an angle to radian
    static double toRadian(double);

    //! Calculates the norm of a vector
    static double norm(btVector3);

    //! Calculates the gaussian
    static double gaussian(double, double);

};

#endif //SDK_RODETAS_MATHHELPER_H
