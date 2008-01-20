#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_alphabeta.h"

AlphaBeta::AlphaBeta() : IA(IS_IA_ALPHABETA)
{
}

int		AlphaBeta::AlgoAlphaBeta(Move **bestMove, int alpha, int beta, int level)
{
    treeNodes++;
    *bestMove = NULL;

    if (Gomoku::GetInstance()->GetGameState() == BOARD_FULL)
        return (0);
    else if (Gomoku::GetInstance()->GetGameState())
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
		(*it)->SetPlayerNumber((PlayerNumber)((Gomoku::GetInstance()->GetNbMoves() % 2) + 1));
        Gomoku::GetInstance()->CommitMove(*it, false);
        val = -AlgoAlphaBeta(&child, -beta, -alpha, level - 1);
        if (child)
            delete child;
        Gomoku::GetInstance()->UndoMove(*it);
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

void	AlphaBeta::findMove()
{
    Move	*bestMove;

    this->treeNodes = 0;
    AlgoAlphaBeta(&bestMove, -INFINITY, INFINITY, DEEP_MAX);
	if (bestMove)
	{
		Gomoku::GetInstance()->CommitMove(bestMove, true);
        //Mainwindow::GetInstance()->UpdateStatistics(this->treeNodes);
	}
}

