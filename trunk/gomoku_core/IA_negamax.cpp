#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_negamax.h"

NegaMax::NegaMax() : IA(IS_IA_NEGAMAX)
{
	this->bestMove = NULL;
	this->gomoku = Gomoku::GetInstance();
    this->treeNodes = 0;
}

int		NegaMax::AlgoNegaMax(int level)
{
    this->treeNodes++;

    if (this->gomoku->GetTmpGameState() == BOARD_FULL)
        return (0);
	else if (this->gomoku->GetTmpGameState() != IN_PROGRESS)
        return (-INFINITY);
    if (!level)
        return (-(this->gomoku->evaluate()));

	unsigned char **board = this->gomoku->GetBoard();
	unsigned int size = this->gomoku->GetSize();
	int best, val;
	
	best = -INFINITY;
	for (unsigned int x = 0; x < size; x++)
		for (unsigned int y = 0; y < size; y++)
			if (board[x][y] == NEUTRAL && this->gomoku->IsCircled(x, y))
			{
				Move *move = new Move(x, y, (PlayerNumber)((this->gomoku->GetNbMoves() % 2) + 1));
				
				if (this->gomoku->CommitMove(move, false) == GOOD_MOVE)
				{
					val = -AlgoNegaMax(level - 1);
					this->gomoku->UndoMove(move);
					if (val > best)
					{
						best = val;
						if (this->bestMove)
							delete this->bestMove;
						this->bestMove = move;
					}
				}
			}
			
    return (best);
}

void	NegaMax::findMove()
{
    this->treeNodes = 0;
    AlgoNegaMax(DEEP_MAX);
    if (this->bestMove)
	{
        Gomoku::GetInstance()->CommitMove(this->bestMove, true);
		this->bestMove = NULL;
    }
}
