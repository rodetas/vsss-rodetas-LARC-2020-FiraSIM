//
// Created by manoel on 12/09/18.
//

#include <Domain/PositionStatus.h>

std::string toString(PositionStatus pos){

    switch (pos){

        case PositionStatus::None:
            return "None";

        case PositionStatus::Penalty:
            return "Penalty";

        case PositionStatus::Freeball:
            return "FreeBall";

        default:
            return "";

    }

}

