//
// Created by manoel on 12/09/18.
//

#include <Domain/PositionStatus.h>

std::string toString(PositionStatus pos){

    switch (pos){

        case PositionStatus::None:
            return "None";

        case PositionStatus::PenaltyHit:
            return "Penalty a favor";

        case PositionStatus::PenaltyAgainst:
            return "Penalty contra";

        case PositionStatus::Freeball:
            return "FreeBall";

        case PositionStatus::MiddleDefense:
            return "Saida de bola contra";

        case PositionStatus::MiddleAttack:
            return "Saida de bola a favor";

        default:
            return "";

    }

}

