//
// Created by paulo on 19/05/18.
//

#include <Movements/UnivectorField.h>
#include <Config.h>

UnivectorField::UnivectorField() {
    n = 2;
    orientationDistance = 15;
    k0 = 0.12;
    dmin = 4.5;
    delta = 4.5;

    offTheField = false;
    insideGoalArea = false;
}

void UnivectorField::setUnivectorWithoutCurves() {
    n = 0;
}

void UnivectorField::setUnivectorWithCurves() {
    n = 2;
    orientationDistance = 15;
}

void UnivectorField::setN(float n) {
    this->n = n;
}

void UnivectorField::setOrientationPointDistance(float distance) {
    orientationDistance = distance;
}



float
UnivectorField::defineFi(RobotState robot, vss::Pose target, std::vector<std::pair<vss::Point, vss::Point>> obstacles) {

    vss::Point arrivalOrientation = getArrivalPoint(target);

    float moveFi = defineMoveFi(robot.position, target, arrivalOrientation);

    //If doesn't exist obstacles, only move fi is returned
    if (obstacles.size() > 0) {

        //For each obstacle, the virtual obstacle is created here
        std::vector<vss::Point> virtualObstacles;
        for (auto &r: obstacles) {
            vss::Point s = getS(robot.vectorSpeed, r.second);
            vss::Point virtualObstacle = getVirtualPosition(robot.position, r.first, s);
            virtualObstacles.push_back(virtualObstacle);
        }

        //Now, the closest virtual obstacle from the robot is found and its distance is saved
        float distance = Math::distancePoint(robot.position, virtualObstacles[0]);
        vss::Point closestVirtualObstacle = virtualObstacles[0];
        for (unsigned i = 1; i < virtualObstacles.size(); i++) {
            float d = Math::distancePoint(robot.position, virtualObstacles[i]);
            if (d < distance) {
                distance = d;
                closestVirtualObstacle = virtualObstacles[i];
            }
        }

        //Calculates the repulsive fi of the closest virtual obstacle
        float repulsiveFi = defineRepulsiveFi(robot.position, closestVirtualObstacle);

        //If the robot is inside of the repulsive radius of the virtual obstacle, only repulsive fi is returned,
        //else a composition with the move fi and the repulsive fi is created with a gaussian function
        if (distance <= dmin) {
            return repulsiveFi;
        } else {
            float g = Math::gaussian(distance - dmin, delta);
            float subtraction = Math::toDomain(repulsiveFi - moveFi);
            float fi = Math::toDomain(g * subtraction) + Math::toDomain(moveFi);
            return Math::toDomain(fi);
        }
    } else {
        return moveFi;
    }
}

vss::Path
UnivectorField::drawPath(RobotState robot, vss::Pose target, std::vector<std::pair<vss::Point, vss::Point>> obstacles) {
    std::vector<vss::Point> points;
    vss::Point point = robot.position;
    RobotState r = robot;

    offTheField = false;
    insideGoalArea = false;

    float fi = defineFi(robot, target, obstacles);
    for (int i = 0; i < 250; i++) {
        point.x = point.x + cos(fi);
        point.y = point.y + sin(fi);
        r.position = point;
        points.push_back(point);
        fi = defineFi(r, target, obstacles);
        if (Math::distancePoint(point, target) < 2)
            i = 250;

        if(point.x < vss::MIN_COORDINATE_X + 15 || point.x > vss::MAX_COORDINATE_X - 15 || point.y < vss::MIN_COORDINATE_Y || point.y > vss::MAX_COORDINATE_Y)
            offTheField = true;

        if(point.y > (vss::MAX_COORDINATE_Y / 2 - Config::goalAreaSize.y / 2) &&
        point.y < (vss::MAX_COORDINATE_Y / 2 + Config::goalAreaSize.y / 2 ) &&
        point.x > vss::MAX_COORDINATE_X - 30)
            insideGoalArea = true;
    }

    vss::Path path;
    path.points = points;

    return path;
}

float UnivectorField::defineMoveFi(vss::Point robot, vss::Pose target, vss::Point arrivalOrientation) {
    //Angle between the robot and the arrival orientation point
    float pr = atan2((arrivalOrientation.y - robot.y), (arrivalOrientation.x - robot.x));
    //Angle between the robot and the target
    float pg = atan2((target.y - robot.y), (target.x - robot.x));

    float alpha = pr - pg;
    float fi = pg - n * alpha;
    return Math::toDomain(fi);
}

float UnivectorField::defineRepulsiveFi(vss::Point robot, vss::Point virtualObstacle) {
    //The repulsive fi is only the angle between the robot and the virtual obstacle
    float fi = Math::radian(robot, virtualObstacle);
    return Math::toDomain(fi);
}

vss::Point UnivectorField::getS(vss::Point robotSpeed, vss::Point obstacleSpeed) {
    // s is a vector of the subtraction of the robot and obstacle speed multiplied by the constant k0
    vss::Point s((obstacleSpeed.x - robotSpeed.x) * k0, (obstacleSpeed.y - robotSpeed.y) * k0);
    return s;
}

vss::Point UnivectorField::getVirtualPosition(vss::Point robot, vss::Point obstacle, vss::Point s) {
    //Calculates the s norm
    float snorm = Math::norm(s);
    //Distance between the obstacle and the robot
    float d = Math::distancePoint(obstacle, robot);
    //Calculates the virtual position with the conditions of the second article
    vss::Point virtualPosition;
    if (d >= snorm) {
        virtualPosition.x = obstacle.x + s.x;
        virtualPosition.y = obstacle.y + s.y;
    } else {
        virtualPosition.x = obstacle.x + s.x * (d / snorm);
        virtualPosition.y = obstacle.y + s.y * (d / snorm);
    }
    return virtualPosition;
}

vss::Point UnivectorField::getArrivalPoint(vss::Pose target) {
    vss::Point arrivalOrientation;
    float angle = target.angle;
    angle = Math::toDomain2Pi(angle);
    float delX;
    float delY;
    float angleAux;

    //Only 0 - 2 * M_PI angles
    if ((angle > 0 || angle == 0) && (angle < 2 * M_PI || angle == 2 * M_PI)) {

        if (angle < M_PI / 2 || angle == M_PI / 2) {

            delX = orientationDistance * cos(angle);
            delY = orientationDistance * sin(angle);

            arrivalOrientation.x = target.x - delX;
            arrivalOrientation.y = target.y + delY;

        } else if (angle < M_PI || angle == M_PI) {

            angleAux = M_PI - angle;
            delX = orientationDistance * cos(angleAux);
            delY = orientationDistance * sin(angleAux);

            arrivalOrientation.x = target.x + delX;
            arrivalOrientation.y = target.y + delY;

        } else if (angle < (3 * M_PI) / 2 || angle == (3 * M_PI) / 2) {

            angleAux = (3 * M_PI) / 2 - angle;
            delX = orientationDistance * sin(angleAux);
            delY = orientationDistance * cos(angleAux);

            arrivalOrientation.x = target.x + delX;
            arrivalOrientation.y = target.y - delY;

        } else if (angle < 2 * M_PI) {

            angleAux = 2 * M_PI - angle;
            delX = orientationDistance * cos(angleAux);
            delY = orientationDistance * sin(angleAux);

            arrivalOrientation.x = target.x - delX;
            arrivalOrientation.y = target.y - delY;
        }
    }

    return arrivalOrientation;
}
