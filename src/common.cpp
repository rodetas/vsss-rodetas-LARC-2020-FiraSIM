/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "common.h"

namespace common{
    double distancePoint(btVector3 a, btVector3 b){
        return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
    }

    btVector3 midpoint(btVector3 a, btVector3 b){
        return btVector3(((a.x + b.x) / 2.0), ((a.y + b.y) / 2.0), 0.0);
    }

    //! Addendum
    //! --------
    //! 
    double angulation(btVector3 a, btVector3 b){
        //! > Estimate angle between two straight lines. 
        //! > One line formed by the two points in the function and 
        //! > the other line is formed by the point in the center of
        //! > the robot (estimated using midpoint() function) and for
        //! > a point in the pitch where the line must form a ninety 
        //! > degree angle with the pitch side.
        return (atan2(a.y - b.y, a.x - b.x) * (180/M_PI));
    }

    double radian(btVector3 a, btVector3 b){
        return atan2(a.y - b.y, a.x - b.x);
    }
};
