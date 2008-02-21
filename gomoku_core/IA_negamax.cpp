#include <cstdlib>
#include <vector>
#include <iostream>

#include "IA_negamax.h"

NegaMax::NegaMax() : IA(IS_IA_NEGAMAX)
{
	this->bestMove = NULL;
	this->gomoku = Gomoku::GetInstance();
    this->treeNodes = 0;
    this->time = 0;
}

int		NegaMax::AlgoNegaMax(vector<pair<int, int> > covering, int level)
{
    this->treeNodes++;

    if (this->gomoku->GetTmpGameState() == BOARD_FULL)
        return (0);
	else if (this->gomoku->GetTmpGameState() != IN_PROGRESS)
        return (-INFINITY);
    if (!level)
        return (-(this->gomoku->evaluate()));

	int best, val;
	
	vector<pair<int, int> >::iterator it = covering.begin();
	vector<pair<int, int> >::iterator eit = covering.end();	
	best = -INFINITY;

	for (; it != eit; it++)
	{
	
		Move *move = new Move(it->first, it->second, (PlayerNumber)((this->gomoku->GetNbMoves() % 2) + 1));
				
		if (this->gomoku->CommitMove(move, false) == GOOD_MOVE)
		{
			val = -AlgoNegaMax(covering, level - 1);
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
	int x = -1, y = -1;
	PlayerNumber p = (PlayerNumber)((Gomoku::GetInstance()->GetNbMoves() % 2) + 1);
	PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;
	
	if (Gomoku::GetInstance()->GetPlayer(adv)->GetPairs() >= 3 &&
		((x = Gomoku::GetInstance()->CounterPairTaking(p, adv).first) != -1 &&
		(y = Gomoku::GetInstance()->CounterPairTaking(p, adv).second) != -1))
	{
		Gomoku::GetInstance()->CommitMove(new Move(x, y, p), true);
	}	
	else if ((x = Gomoku::GetInstance()->OneMoveWin(p).first) != -1 &&
			 (y = Gomoku::GetInstance()->OneMoveWin(p).second) != -1)
	{
		Gomoku::GetInstance()->CommitMove(new Move(x, y, p), true);
	}
	else
	{
		QTime chronometer;
		vector<pair<int, int> > covering = Gomoku::GetInstance()->BuildCovering();

		this->treeNodes = 0;
		chronometer.start();
		AlgoNegaMax(covering, DEEP_MAX);
		this->time = chronometer.elapsed();
		if (this->bestMove)
		{
			Gomoku::GetInstance()->CommitMove(this->bestMove, true);
			this->bestMove = NULL;
		}
	}
}
