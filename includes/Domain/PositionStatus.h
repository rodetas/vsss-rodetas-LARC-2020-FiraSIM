//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_POSITIONSTATUS_H
#define SDK_RODETAS_POSITIONSTATUS_H

#include <string>

// @TODO diferenciar penalti na defesa e penalti no ataque
// @TODO diferenciar freeball na defesa e no ataque
// @TODO considerar situacao de tiro de meta
// @TODO situação de gol contra e gol a favor

enum class PositionStatus {

    None,
    Penalty,
    Freeball

};

std::string toString(PositionStatus);

#endif //SDK_RODETAS_POSITIONSTATUS_H
