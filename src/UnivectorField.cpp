//
// Created by paulo on 19/05/18.
//

#include <UnivectorField.h>

UnivectorField::UnivectorField(float n, float k0, float dmin, float delta) : n(n), k0(k0), dmin(dmin), delta(delta) {}

UnivectorField::UnivectorField() {}

float UnivectorField::defineMoveFi(btVector3 robot, btVector3 target, btVector3 arrivalOrientation) {

    float pr = atan2((arrivalOrientation.y - robot.y), (arrivalOrientation.x - robot.x));
    float pg = atan2((target.y - robot.y), (target.x - robot.x));

    float alpha = pr - pg;
    float fi = pg - n * alpha;
    return fi;
}

float UnivectorField::defineRepulsiveFi(btVector3 robot, btVector3 virtualObstacle) {
    float fi = Math::radian(robot, virtualObstacle);
    return fi;
}

float
UnivectorField::defineFi(RobotState robot, btVector3 robotPosition, btVector3 target, btVector3 arrivalOrientation,
                         std::vector<RobotState> robots) {
    btVector3 robotSpeed = robot.vectorSpeed;

    float moveFi = defineMoveFi(robotPosition, target, arrivalOrientation);

    std::vector<btVector3> virtualObstacles;
    for (auto &r: robots) {
        if ((r.position.x != robot.position.x) && (r.position.y != robot.position.y)) {
            btVector3 obstaclePosition = r.position;
            btVector3 obstacleSpeed = r.vectorSpeed;
            btVector3 s = getS(robotSpeed, obstacleSpeed);
            btVector3 virtualObstacle = getVirtualPosition(robotPosition, obstaclePosition, s);
            virtualObstacles.push_back(virtualObstacle);
        }
    }
    if (virtualObstacles.size() > 0) {
        float distance = Math::distancePoint(robotPosition, virtualObstacles[0]);
        btVector3 closestVirtualObstacle = virtualObstacles[0];
        for (unsigned i = 1; i < virtualObstacles.size(); i++) {
            float d = Math::distancePoint(robotPosition, virtualObstacles[i]);
            if (d < distance) {
                distance = d;
                closestVirtualObstacle = virtualObstacles[i];
            }
        }

        float repulsiveFi = defineRepulsiveFi(robotPosition, closestVirtualObstacle);

        if (distance <= dmin) {
            return repulsiveFi;
        } else {
            float g = Math::gaussian(distance - dmin, delta);
            float diff = repulsiveFi - moveFi;
            return (g * diff + moveFi);
        }
    } else {
        return moveFi;
    }
}

btVector3 UnivectorField::getS(btVector3 robotSpeed, btVector3 obstacleSpeed) {
    btVector3 s((obstacleSpeed.x - robotSpeed.x) * k0, (obstacleSpeed.y - robotSpeed.y) * k0);
    return s;
}

btVector3 UnivectorField::getVirtualPosition(btVector3 robot, btVector3 obstacle, btVector3 s) {
    float snorm = Math::norm(s);
    float d = Math::distancePoint(obstacle, robot);
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
