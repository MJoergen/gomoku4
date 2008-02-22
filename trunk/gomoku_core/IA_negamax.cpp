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

int		NegaMax::AlgoNegaMax(vector<pair<int, int> > *covering, int level)
{
    this->treeNodes++;

    if (this->gomoku->GetTmpGameState() == BOARD_FULL)
        return (0);
	else if (this->gomoku->GetTmpGameState() != IN_PROGRESS)
        return (-INFINITY);
    if (!level)
        return (-(this->gomoku->evaluate()));

	int best, val;
	
	vector<pair<int, int> >::iterator it = covering->begin();
	vector<pair<int, int> >::iterator eit = covering->end();	
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
	PlayerNumber p = (PlayerNumber)((Gomoku::GetInstance()->GetNbMoves() % 2) + 1);
	PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;
	pair<int, int> Counter = Gomoku::GetInstance()->CounterPairTaking(p, adv);
	pair<int, int> oneMove = Gomoku::GetInstance()->OneMoveWin(p);
	
	if (Gomoku::GetInstance()->GetPlayer(adv)->GetPairs() >= 3 &&
		(Counter.first != -1 && Counter.second != -1))
	{
		Gomoku::GetInstance()->CommitMove(new Move(Counter.first, Counter.second, p), true);
	}	
	else if (oneMove.first != -1 && oneMove.second != -1)
	{
		Gomoku::GetInstance()->CommitMove(new Move(oneMove.first, oneMove.second, p), true);
	}
	else
	{
		QTime chronometer;
		vector<pair<int, int> > *covering = new vector<pair<int, int> >;
		
		this->treeNodes = 0;
		Gomoku::GetInstance()->BuildCovering(covering);
		chronometer.start();
		AlgoNegaMax(covering, DEEP_MAX);
		this->time = chronometer.elapsed();
		if (this->bestMove)
		{
			Gomoku::GetInstance()->CommitMove(new Move(this->bestMove->GetX(), this->bestMove->GetY(), p), true);
			this->bestMove = NULL;
		}
	}
}
