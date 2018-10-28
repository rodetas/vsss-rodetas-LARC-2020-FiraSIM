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

double Math::radian(vss::Point a, vss::Point b) {
    return atan2(a.y - b.y, a.x - b.x);
}

double Math::calculateLinearSpeed(double velX, double velY) {
    return sqrt(pow(velX / 3, 2) + pow(velY / 3, 2));
}

vss::Point Math::calculateProjection(vss::Point initialPoint, double velX, double velY) {
    return vss::Point(initialPoint.x + velX / 3, initialPoint.y + velY / 3);
}

double Math::toRadian(double angle) {
    return angle * (M_PI / 180);
}

double Math::norm(vss::Point vector) {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

double Math::gaussian(double r, double delta) {
    return exp(-((r * r) / (2 * delta * delta)));
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