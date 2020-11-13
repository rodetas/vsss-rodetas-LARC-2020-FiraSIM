//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MATHHELPER_H
#define SDK_RODETAS_MATHHELPER_H

#include <Domain/Point.h>
#include <cmath>
#include <Config.h>

class Math {

public:
    //! Estimate distance between a set of points.
    static double distancePoint(vss::Point, vss::Point);

    //! Estimate angle between two straight lines.
    static double angulation(vss::Point, vss::Point);

    static double angulation2(vss::Point, vss::Point);

    //! Estimate angle between two straight lines in radian.
    static double radian(vss::Point, vss::Point);

    static double calculateLinearSpeed(double, double);

    //! Given a initial point and two velocities returns the initial point projection considering these two velocities
    static vss::Point calculateProjection(vss::Point, double, double);

    //! Transforms an angle to radian
    static double toRadian(double);

    static double toDegree(double);

    static vss::Point conversionYellow(vss::Point);
    
    static vss::Point conversionBlue(vss::Point);

    //! Calculates the norm of a vector
    static double norm(vss::Point);

    //! Calculates the gaussian
    static double gaussian(double, double);

    //! Keeps the angle in the domain [-PI, PI]
    static float toDomain(float fi);

    //! Keeps the angle in the domain [0, 2PI]
    static float toDomain2Pi(float fi);

    //! Calculates the arrival angle
    template <typename T, typename U>
    static float arrivalAngle(T target, U orientation){
        if(target.y <= orientation.y){
            return atan2(orientation.y - target.y, target.x - orientation.x);
        }
        else{
            return - atan2(target.y - orientation.y, target.x - orientation.x);
        }
    }
    template <typename T, typename U>
    static float arrivalAngle2(T target, U orientation){
        float a1, a2, a3, a4;
        if(target.y <= orientation.y){
            a1 = atan2((orientation.y - Config::goalSize.y /2) - target.y,(target.x - orientation.x));
            a2 = atan2(orientation.y - target.y, target.x - orientation.x);
            a3 = atan2((orientation.y + Config::goalSize.y /2) - target.y,(target.x - orientation.x));
            return (a1+a3 -2*a2);
            //return a3 - a2;
        }
        else{
            a1 = atan2(target.y -(orientation.y + Config::goalSize.y/2),(orientation.x - target.x));
            a2 = atan2(target.y - orientation.y, orientation.x - target.x);
            a3 = atan2(target.y -(orientation.y - Config::goalSize.y/2),(orientation.x - target.x));
            return (a1 + a3 - 2*a2)*-1;
            //return M_PI -(a3-a1);
            //return a3 - a2;
        }
    }

};

#endif //SDK_RODETAS_MATHHELPER_H
