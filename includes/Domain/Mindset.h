//
// Created by manoel on 16/04/18.
//

#ifndef SDK_RODETAS_MINDSET_H
#define SDK_RODETAS_MINDSET_H

#include <string>
#include <vector>

enum class MindSet {
    None,
    GoalKeeperStrategy,      // estrategia goleiro
    DefenderStrategy,        // estrategia defensor
    DefenderStrategyLeft,    // estrategia defensor da esquerda
    DefenderStrategyRight,   // estrategia defensor da direita
    DefenderBackStrategy,    // estrategia defensor fazendo linha de defesa
    AttackerStrategy,        // estrategia do atacante
    SideAttackerStrategy,    //estrategia do atacante lateral
    CenterAttackerStrategy,  //estrategia do atacante central
    ForwardAttackerStrategy, //estrategia do atacante que vai reto
    AttackDefenseStrategy,   //estrategia do atacante na defesa

    PenaltyHitAttackPositioning,        // posicionamento para atacante bater penalti
    PenaltyHitDefenderPositioning,      // posicionamento do defensor situacao de penalti a favor

    PenaltyAgainstAttackPositioning,    // posicionamento do atacante em caso de penalti contra
    PenaltyAgainstDefenderPositioning,  // posicionamento do defensor em caso de penalti contra

    AttackMiddleAttackPositioning,      // posicionamento do atacante na saída no meio a favor
    DefenderMiddleAttackPositioning,    // posicionamento do defensor na saída no meio a favor

    AttackMiddleDefensePositioning,     // posicionamento do atacante na saída no meio contra
    DefenderMiddleDefensePositioning,   // posicionamento do defensor na saída no meio contra

    GoalKeeperCenterPositioning         // posiciona o goleiro no centro do gol

    //@TODO definir posicionamento de diversos outros cenarios como freeball, saida de bola(contra e a favor), tiro de meta, etc
};


std::vector<MindSet> getStrategiesMindSet();

std::string toString(MindSet);

#endif //SDK_RODETAS_MINDSET_H
