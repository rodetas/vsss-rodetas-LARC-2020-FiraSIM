/*
 * This file is part of the VSS-SampleStrategy project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <Domain/Point.h>
#include <Domain/WheelsCommand.h>
#include <iomanip>
#include <vector>
#include <sstream>

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
            } else if(c.rightVel == 0 && c.leftVel == 0){
                direction = 'S';
            } else {
                direction = 'F';
            }

            left  = (int)(255 * abs(c.leftVel)) / 100;
            right = (int)(255 * abs(c.rightVel)) / 100;
        }

        virtual std::string to_string(){
            std::stringstream ss;
            ss << direction;
            ss << std::setfill('0') << std::setw(3) << left;
            ss << std::setfill('0') << std::setw(3) << right;
            return ss.str();
        }

        virtual std::vector<int> to_hex(){
            std::string cmd = this->to_string();
            std::vector<int> vec;

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
