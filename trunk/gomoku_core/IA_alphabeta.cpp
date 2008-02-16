#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_alphabeta.h"

AlphaBeta::AlphaBeta() : IA(IS_IA_ALPHABETA)
{
	this->bestMove = NULL;
	this->gomoku = Gomoku::GetInstance();
    this->treeNodes = 0;
    this->time = 0;
}

int		AlphaBeta::AlgoAlphaBeta(int alpha, int beta, int level)
{
    this->treeNodes++;

	if (Gomoku::GetInstance()->GetTmpGameState() == BOARD_FULL)
		return (0);
	else if (Gomoku::GetInstance()->GetTmpGameState() != IN_PROGRESS)
		return (-INFINITY);
    if (!level)
        return (-(this->gomoku->evaluate()));

	unsigned char **board = this->gomoku->GetBoard();
	int size = this->gomoku->GetSize();
	int val;

	for (unsigned int x = 0; x < (unsigned int)size; x++)
		for (unsigned int y = 0; y < (unsigned int)size; y++)
			if (board[x][y] == NEUTRAL && this->gomoku->IsCircled(x, y))
			{
				Move *move = new Move(x, y, (PlayerNumber)((this->gomoku->GetNbMoves() % 2) + 1));
				
				if (this->gomoku->CommitMove(move, false) == GOOD_MOVE)
				{
					val = -AlgoAlphaBeta(-beta, -alpha, level - 1);
					this->gomoku->UndoMove(move);
					if (val > alpha)
					{
						alpha = val;
						if (this->bestMove)
							delete this->bestMove;
						this->bestMove = move;
					}
					if (alpha >= beta)
					{
						alpha = beta;
						break;
					}
				}
			}	
	return (alpha);	
}

void	AlphaBeta::findMove()
{
    QTime chronometer;

	this->treeNodes = 0;
	chronometer.start();
    AlgoAlphaBeta(-INFINITY, INFINITY, DEEP_MAX);
    this->time = chronometer.elapsed();
	if (this->bestMove)
	{
        Gomoku::GetInstance()->CommitMove(this->bestMove, true);
		this->bestMove = NULL;
	}
}
