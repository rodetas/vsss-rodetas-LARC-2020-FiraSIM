//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MATHHELPER_H
#define SDK_RODETAS_MATHHELPER_H

#include <Domain/Point.h>
#include <cmath>

class Math {

public:
    //! Estimate distance between a set of points.
    static double distancePoint(vss::Point, vss::Point);

    //! Estimate angle between two straight lines.
    static double angulation(vss::Point, vss::Point);

    //! Estimate angle between two straight lines in radian.
    static double radian(vss::Point, vss::Point);

    static double calculateLinearSpeed(double, double);

    //! Given a initial point and two velocities returns the initial point projection considering these two velocities
    static vss::Point calculateProjection(vss::Point, double, double);

    //! Transforms an angle to radian
    static double toRadian(double);

    //! Calculates the norm of a vector
    static double norm(vss::Point);

    //! Calculates the gaussian
    static double gaussian(double, double);

    //! Keeps the angle in the domain [-PI, PI]
    static float toDomain(float fi);

};

#endif //SDK_RODETAS_MATHHELPER_H
