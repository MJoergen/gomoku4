#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_alphabeta.h"

int	AlphaBeta::AlgoAlphaBeta(Move **bestMove, int alpha, int beta, int level)
{
    treeNodes++;
    *bestMove = NULL;

    if (Game::GetInstance()->getState() == FULL_BOARD)
        return (0);
    else if (Game::GetInstance()->getState())
        return (-INFINITY);
    if (!level)
        return (-(Game::GetInstance()->evaluate()));

    std::vector<Move*>	moves = Game::GetInstance()->getCorrectMoves();
    Move *child;
    int val;

    *bestMove = moves[0];
    std::vector<Move*>::iterator it = moves.begin();
    std::vector<Move*>::iterator eit = moves.end();

    for (; it != eit; it++)
    {
        Game::GetInstance()->commitMove(*it);
        val = -AlgoAlphaBeta(&child, -beta, -alpha, level - 1);
        if (child)
            delete child;
        Game::GetInstance()->undoMove(*it);
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
    treeNodes = 0;
    AlgoAlphaBeta(&bestMove, -INFINITY, INFINITY, DEEP_MAX);
    std::cout << "<< alphabeta >>" << std::endl << "noeuds: " << treeNodes << std::endl;
    Game::GetInstance()->commitMove(bestMove);
}

