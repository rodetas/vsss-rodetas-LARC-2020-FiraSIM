/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "iostream"
#include "iomanip"
#include "math.h"
#include <interface.h>
//#include "VSS-Interface/cpp/interface.h"

using namespace std;

namespace common{
    enum { NONE = 0, GOAL_TEAM1 = 1, GOAL_TEAM2 = 2, FAULT_TEAM1 = 3, FAULT_TEAM2 = 4, PENALTY_TEAM1 = 5, PENALTY_TEAM2 = 6 };

    //! This struct represents a Vector in R^3.
    struct btVector3{
        //! Data: x, y, z.
        float x, y, z;
        //! Default constructor: btVector3 bt3;
        btVector3(){
            x = y = z = 0;
        };
        //! Construtor XYZ: btVector3 bt3(x, y, z);
        btVector3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        };
        //! Construtor XY: btVector3 bt3(x, y);
        btVector3(float x, float y){
            this->x = x;
            this->y = y;
            this->z = 0;
        };
        //! Constructor copy: btVector3 bt3(btVector3(x, y, z));
        btVector3(btVector3 *b){
            x = b->x;
            y = b->y;
            z = b->z;
        };

        //! Default function: prints all variables.
        string toString(){
            stringstream ss;
            ss << "btVector3(" << x << ", " << y << ", " << z << ")";
            return ss.str();
        };
    };

    //! This is a simple structure responsible for represent a path: vector of poses.
	struct Path{
		vector<btVector3> poses;
		Path(){};
		Path(Path *path){
			poses = path->poses;
		};
		void show(){
			for(unsigned int i = 0 ; i < poses.size() ; i++)
			cout << "(" << poses.at(i).x << ", " << poses.at(i).y << ", " << poses.at(i).z << ")" << endl;
		}
	};

    //! This is a simple structure that represents a Debug packet
    struct Debug{
        btVector3 robots_step_pose[3];
        btVector3 robots_final_pose[3];
        Path robots_path[3];
        Debug(){};
    };

    struct Command{
        float left;
        float right;
        Command(){
            left = right = 0;
        };
        Command(float left, float right){
            this->left = left;
            this->right = right;
        };

        Command(Command *cmd){
            left = cmd->left;
            right = cmd->right;
        };

        string to_string(){
    		stringstream ss;
    		ss << setfill('0') << setw(3) << left;
    		ss << setfill('0') << setw(3) << right;
    		return ss.str();
    	}

    	friend std::ostream& operator<< (std::ostream& stream, const Command& c) {
    		stream << c.left << " " << c.right;
    		return stream;
        }

    	vector<int> to_hex(){
    		string cmd = this->to_string();
    		vector<int> vec;

    		for(unsigned int i=0 ; i<cmd.size() ; i++){
    			vec.push_back(int(cmd[i]));
    		}

    		return vec;
    	}
    };

    //! Estimate distance between a set of points.
    double distancePoint(btVector3, btVector3);

    //! Estimate midpoint between a set of points.
    btVector3 midpoint(btVector3, btVector3);

    //! Estimate angle between two straight lines.
    double angulation(btVector3, btVector3);

    //! Estimate angle between two straight lines in radian.
    double radian(btVector3, btVector3);

    typedef btVector3 Point;
}

#endif
