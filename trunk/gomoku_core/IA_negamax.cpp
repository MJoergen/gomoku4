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

    if (this->gomoku->GetGameState() == BOARD_FULL)
        return (0);
    else if (this->gomoku->GetGameState() == (GameState)((this->gomoku->GetNbMoves() % 2) + 1))
        return (INFINITY);
	else if (this->gomoku->GetGameState())
        return (-INFINITY);
    if (!level)
        return (this->gomoku->evaluate());

	unsigned char **board = this->gomoku->GetBoard();
	int size = this->gomoku->GetSize();
	int best, val;

    best = -INFINITY;

	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
    {
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
		else
			delete move;
		}
		else
			delete move;
		}
    }
    return (best);
}

void	NegaMax::findMove()
{
    this->treeNodes = 0;
    AlgoNegaMax(DEEP_MAX);
    if (this->bestMove)
<<<<<<< .mine
		qDebug("On Commit : x(%d) y(%d)", this->bestMove->GetX(), this->bestMove->GetY());
        Gomoku::GetInstance()->CommitMove(this->bestMove, true);
		qDebug("Et on dit bravo a la vie");
		//delete this->bestMove;
		this->bestMove = NULL;
    }
=======
        Gomoku::GetInstance()->CommitMove(bestMove, true);
>>>>>>> .r129
}
