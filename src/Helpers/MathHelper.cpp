//
// Created by manoel on 16/04/18.
//

#include <Helpers/MathHelper.h>

double Math::distancePoint(vss::Point a, vss::Point b) {
    return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

double Math::angulation(vss::Point a, vss::Point b) {
    return (atan2(a.y - b.y, a.x - b.x) * (180 / M_PI));
}
double Math::angulation2(vss::Point a, vss::Point b) {
    return (atan2(a.y - b.y, a.x - b.x));
}
double Math::radian(vss::Point a, vss::Point b) {
    return atan2(a.y - b.y, a.x - b.x);
}

double Math::calculateLinearSpeed(double velX, double velY) {
    return sqrt(pow(velX, 2) + pow(velY, 2));
}

vss::Point Math::calculateProjection(vss::Point initialPoint, double velX, double velY) {
    return vss::Point(initialPoint.x + velX / 3, initialPoint.y + velY / 3);
}

double Math::toRadian(double angle) {
    return angle * (M_PI / 180);
}

double Math::toDegree(double angle) {
    return (angle) * (180 / M_PI);
}

vss::Point Math::conversion(vss::Point a){
    return vss::Point((a.x*100)+75,(130-(a.y*100+65)));
}

double Math::norm(vss::Point vector) {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

double Math::gaussian(double r, double delta) {
    return exp(-((r * r) / (2 * delta * delta)));
    //return exp(-(r)/delta);
}

float Math::toDomain(float fi) {
    if (fi > M_PI) {
        return (fi - 2 * M_PI);
    } else if (fi < -M_PI) {
        return (2 * M_PI + fi);
    } else {
        return fi;
    }
}

float Math::toDomain2Pi(float angle) {
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}