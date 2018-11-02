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

        case PositionStatus::FreeballLeftAttack:
            return "Freeball ataque esquerdo";

        case PositionStatus::FreeballRightAttack:
            return "Freeball ataque direito";

        case PositionStatus::FreeballLeftDefense:
            return "Freeball defesa esquerda";

        case PositionStatus::FreeballRightDefense:
            return "Freeball defesa direita";

        default:
            return "";

    }

}

