//
// Created by manoel on 31/08/18.
//

#ifndef SDK_RODETAS_POSITIONSTATUS_H
#define SDK_RODETAS_POSITIONSTATUS_H

// @TODO diferenciar penalti na defesa e penalti no ataque
// @TODO diferenciar freeball na defesa e no ataque
// @TODO considerar situacao de tiro de meta
// @TODO situação de gol contra e gol a favor

enum class PositionStatus {

    None,
    Penalty,
    Freeball

};

#endif //SDK_RODETAS_POSITIONSTATUS_H
