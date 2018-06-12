//
// Created by paulo on 19/05/18.
//

#include <UnivectorField.h>

UnivectorField::UnivectorField(float n, float k0, float dmin, float delta) : n(n), k0(k0), dmin(dmin), delta(delta) {}

UnivectorField::UnivectorField() {}

float UnivectorField::defineFi(RobotState robot, btVector3 target, btVector3 arrivalOrientation,
                               vector<pair<btVector3, btVector3>> obstacles) {

    float moveFi = defineMoveFi(robot.position, target, arrivalOrientation);

    //If doesn't exist obstacles, only move fi is returned
    if (obstacles.size() > 0) {

        //For each obstacle, the virtual obstacle is created here
        std::vector<btVector3> virtualObstacles;
        for (auto &r: obstacles) {
            btVector3 s = getS(robot.vectorSpeed, r.second);
            btVector3 virtualObstacle = getVirtualPosition(robot.position, r.first, s);
            virtualObstacles.push_back(virtualObstacle);
        }

        //Now, the closest virtual obstacle from the robot is found and its distance is saved
        float distance = Math::distancePoint(robot.position, virtualObstacles[0]);
        btVector3 closestVirtualObstacle = virtualObstacles[0];
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
            float subtraction = toDomain(repulsiveFi - moveFi);
            float fi = toDomain(g * subtraction) + toDomain(moveFi);
            return toDomain(fi);
        }
    } else {
        return moveFi;
    }
}

Path UnivectorField::drawPath(RobotState robot, btVector3 target, btVector3 arrivalOrientation,
                              vector<pair<btVector3, btVector3>> obstacles) {
    vector<btVector3> points;
    btVector3 point = robot.position;
    RobotState r = robot;

    float fi = defineFi(robot, target, arrivalOrientation, obstacles);
    for (int i = 0; i < 250; i++) {
        point.x = point.x + cos(fi);
        point.y = point.y + sin(fi);
        r.position = point;
        points.push_back(point);
        fi = defineFi(r, target, arrivalOrientation, obstacles);
        if (Math::distancePoint(point, target) < 2)
            i = 250;
    }
    Path path;
    path.poses = points;
    return path;
}

float UnivectorField::defineMoveFi(btVector3 robot, btVector3 target, btVector3 arrivalOrientation) {
    //Angle between the robot and the arrival orientation point
    float pr = atan2((arrivalOrientation.y - robot.y), (arrivalOrientation.x - robot.x));
    //Angle between the robot and the target
    float pg = atan2((target.y - robot.y), (target.x - robot.x));

    float alpha = pr - pg;
    float fi = pg - n * alpha;
    return toDomain(fi);
}

float UnivectorField::defineRepulsiveFi(btVector3 robot, btVector3 virtualObstacle) {
    //The repulsive fi is only the angle between the robot and the virtual obstacle
    float fi = Math::radian(robot, virtualObstacle);
    return toDomain(fi);
}

btVector3 UnivectorField::getS(btVector3 robotSpeed, btVector3 obstacleSpeed) {
    // s is a vector of the subtraction of the robot and obstacle speed multiplied by the constant k0
    btVector3 s((obstacleSpeed.x - robotSpeed.x) * k0, (obstacleSpeed.y - robotSpeed.y) * k0);
    return s;
}

btVector3 UnivectorField::getVirtualPosition(btVector3 robot, btVector3 obstacle, btVector3 s) {
    //Calculates the s norm
    float snorm = Math::norm(s);
    //Distance between the obstacle and the robot
    float d = Math::distancePoint(obstacle, robot);
    //Calculates the virtual position with the conditions of the second article
    btVector3 virtualPosition;
    if (d >= snorm) {
        virtualPosition.x = obstacle.x + s.x;
        virtualPosition.y = obstacle.y + s.y;
    } else {
        virtualPosition.x = obstacle.x + s.x * (d / snorm);
        virtualPosition.y = obstacle.y + s.y * (d / snorm);
    }
    return virtualPosition;
}

float UnivectorField::toDomain(float fi) {
    if (fi > M_PI) {
        return (fi - 2 * M_PI);
    } else if (fi < -M_PI) {
        return (2 * M_PI + fi);
    } else {
        return fi;
    }
}
