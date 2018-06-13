/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <interface.h>

using namespace std;

namespace common{
    enum { none = 0, goalTeam1 = 1, goalTeam2 = 2, faultTeam1 = 3, faultTeam2 = 4, penaltyTeam1 = 5, penaltyTeam2 = 6 };

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
        explicit btVector3(btVector3 *b){
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

		Path() = default;

		explicit Path(Path *path){
			poses = path->poses;
		};

		void show(){
			for(auto pose : poses)
			    cout << "(" << pose.x << ", " << pose.y << ", " << pose.z << ")" << endl;
		}
	};

    //! This is a simple structure that represents a Debug packet
    struct Debug{
        btVector3 robotsStepPose[3];
        btVector3 robotsFinalPose[3];
        Path robotsPath[3];
        Debug() = default;
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

        explicit Command(Command *cmd){
            left = cmd->left;
            right = cmd->right;
        };

        virtual string to_string(){
    		stringstream ss;
    		ss << setfill('0') << setw(3) << left;
    		ss << setfill('0') << setw(3) << right;
    		return ss.str();
    	}

    	friend std::ostream& operator<< (std::ostream& stream, const Command& c) {
    		stream << c.left << " " << c.right;
    		return stream;
        }

    	virtual vector<int> to_hex(){
    		string cmd = this->to_string();
    		vector<int> vec;

    		for(const auto _cmd : cmd){
    			vec.push_back(int(_cmd));
    		}

    		return vec;
    	}
    };

    struct OldCommand  : public Command {

        char direction;

        OldCommand(){
            left = 0;
            right = 0;
            direction = 'F';
        }

        explicit OldCommand(Command c){

            if(c.left < 0 and c.right < 0){
                direction = 'B';
            } else if(c.left < 0){
                direction = 'L';
            } else if(c.right < 0){
                direction = 'R';
            } else {
                direction = 'F';
            }

            left = (int)(255*abs(c.left))/80;
            right = (int)(255*abs(c.right))/80;

            //std::cout << direction << " " << left << " " << right << std::endl;
        }

        virtual string to_string(){
            stringstream ss;
            ss << direction;
            ss << setfill('0') << setw(3) << left;
            ss << setfill('0') << setw(3) << right;
            return ss.str();
        }

        virtual vector<int> to_hex(){
            string cmd = this->to_string();
            vector<int> vec;

            for(const auto _cmd : cmd){
                vec.push_back(int(_cmd));
            }

            return vec;
        }

    };
}

#endif
