//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MINDSET_H
#define SDK_RODETAS_MINDSET_H

#include <string>
#include <vector>

enum class MindSet {
    None,
    GoalKeeperStrategy,     // estrategia goleiro
    DefenderStrategy,       // estrategia defensor
    DefenderBackStrategy,   // estrategia defensor fazendo linha de defesa
    AttackerStrategy,       // estrategia do atacante

    PenaltyHitAttackPositioning,        // posicionamento para atacante bater penalti
    PenaltyHitDefenderPositioning,      // posicionamento do defensor situacao de penalti a favor

    PenaltyAgainstAttackPositioning,    // posicionamento do atacante em caso de penalti contra
    PenaltyAgainstDefenderPositioning,  // posicionamento do defensor em caso de penalti contra

    GoalKeeperCenterPositioning         // posiciona o goleiro no centro do gol

    //@TODO definir posicionamento de diversos outros cenarios como freeball, saida de bola(contra e a favor), tiro de meta, etc
};


std::vector<MindSet> getStrategiesMindSet();

std::string toString(MindSet);

#endif //SDK_RODETAS_MINDSET_H
