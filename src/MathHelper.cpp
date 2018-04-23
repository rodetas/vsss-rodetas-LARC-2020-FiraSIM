//
// Created by manoel on 16/04/18.
//

#include <MathHelper.h>

double Math::distancePoint(btVector3 a, btVector3 b){
    return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
}

double Math::angulation(btVector3 a, btVector3 b){
    return (atan2(a.y - b.y, a.x - b.x) * (180/M_PI));
}

double Math::radian(btVector3 a, btVector3 b){
    return atan2(a.y - b.y, a.x - b.x);
}

double Math::calculateLinearSpeed(double velX, double velY){
    return sqrt(pow(velX,2) + pow(velY,2));
}

btVector3 Math::calculateProjection(btVector3 initialPoint, double velX, double velY) {
    return btVector3(initialPoint.x + velX, initialPoint.y + velY);
}
