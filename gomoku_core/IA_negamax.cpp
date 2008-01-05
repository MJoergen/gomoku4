#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_negamax.h"

int	NegaMax::AlgoNegaMax(Move **bestMove, int level)
{
    treeNodes++;
    *bestMove = NULL;

    if (Gomoku::GetInstance()->getState() == FULL_BOARD)
        return (0);
    else if (Gomoku::GetInstance()->getState())
        return (-INFINITY);
    if (!level)
        return (-(Gomoku::GetInstance()->evaluate()));

    std::vector<Move *> moves = Gomoku::GetInstance()->getCorrectMoves();
    Move *child;
    int best, val;

    *bestMove = moves[0];
    best = -INFINITY;
    std::vector<Move *>::iterator it = moves.begin();
    std::vector<Move *>::iterator eit = moves.end();

    for (; it != eit; it++)
    {
        Gomoku::GetInstance()->commitMove(*it, false);
        val = -AlgoNegaMax(&child, level - 1);
        if (child)
            delete child;
        Gomoku::GetInstance()->undoMove(*it);
        if (val > best)
        {
            best = val;
            *bestMove = *it;
        }
    }
    for (it = moves.begin(); it != eit; it++)
        if (*it != *bestMove)
            delete *it;
    return (best);
}

void	NegaMax::findMove()
{
    Move *bestMove;

    this->treeNodes = 0;
    AlgoNegaMax(&bestMove, DEEP_MAX);
    if (bestMove)
    {
        Gomoku::GetInstance()->commitMove(bestMove, true);
        Mainwindow::GetInstance()->UpdateStatistics(this->treeNodes);
    }
}
