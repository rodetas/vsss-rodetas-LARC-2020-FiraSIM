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
#include <Domain/Point.h>
#include <vector>
#include <sstream>
#include <Domain/WheelsCommand.h>

using namespace std;

namespace common{

    struct OldCommand {

        int left;
        int right;
        char direction;

        OldCommand(){
            left = 0;
            right = 0;
            direction = 'F';
        }

        explicit OldCommand(vss::WheelsCommand c){

            if(c.leftVel < 0 and c.rightVel < 0){
                direction = 'B';
            } else if(c.leftVel < 0){
                direction = 'L';
            } else if(c.rightVel < 0){
                direction = 'R';
            } else {
                direction = 'F';
            }

            left = (int)(255*abs(c.leftVel))/80;
            right = (int)(255*abs(c.rightVel))/80;
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

        friend std::ostream& operator<< (std::ostream& stream, const OldCommand& c) {
            stream << c.direction << " " << c.left << " " << c.right;
            return stream;
        }

    };
}

#endif
