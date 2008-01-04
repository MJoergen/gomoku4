#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_alphabeta.h"

int	AlphaBeta::AlgoAlphaBeta(Move **bestMove, int alpha, int beta, int level)
{
    treeNodes++;
    *bestMove = NULL;

    if (Gomoku::GetInstance()->getState() == FULL_BOARD)
        return (0);
    else if (Gomoku::GetInstance()->getState())
        return (-INFINITY);
    if (!level)
        return (-(Gomoku::GetInstance()->evaluate()));

    std::vector<Move*>	moves = Gomoku::GetInstance()->getCorrectMoves();
    Move *child;
    int val;

    *bestMove = moves[0];
    std::vector<Move*>::iterator it = moves.begin();
    std::vector<Move*>::iterator eit = moves.end();

    for (; it != eit; it++)
    {
        Gomoku::GetInstance()->commitMove(*it, false);
        val = -AlgoAlphaBeta(&child, -beta, -alpha, level - 1);
        if (child)
            delete child;
        Gomoku::GetInstance()->undoMove(*it);
        if (val > alpha)
        {
            alpha = val;
            *bestMove = *it;
        }
        if (alpha >= beta)
        {
            alpha = beta;
            break;
        }
    }
    for (it = moves.begin(); it != eit; it++)
        if (*it != *bestMove)
            delete *it;
    return (alpha);
}

void    AlphaBeta::findMove()
{
    Move	*bestMove;

    this->treeNodes = 0;
    AlgoAlphaBeta(&bestMove, -INFINITY, INFINITY, DEEP_MAX);
    Mainwindow::GetInstance()->UpdateStatistics(this->treeNodes);
	if (bestMove)
		Gomoku::GetInstance()->commitMove(bestMove, true);
}

