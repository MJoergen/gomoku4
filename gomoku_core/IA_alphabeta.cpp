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

int		AlphaBeta::AlgoAlphaBeta(vector<pair<int, int> > covering, int alpha, int beta, int level)
{
    this->treeNodes++;

	if (Gomoku::GetInstance()->GetTmpGameState() == BOARD_FULL)
		return (0);
	else if (Gomoku::GetInstance()->GetTmpGameState() != IN_PROGRESS)
		return (-INFINITY);
    if (!level)
        return (-(this->gomoku->evaluate()));

	int val;
	vector<pair<int, int> >::iterator it = covering.begin();
	vector<pair<int, int> >::iterator eit = covering.end();

	for (; it != eit; it++)
	{
		Move *move = new Move(it->first, it->second, (PlayerNumber)((this->gomoku->GetNbMoves() % 2) + 1));
				
		if (this->gomoku->CommitMove(move, false) == GOOD_MOVE)
		{
			val = -AlgoAlphaBeta(covering, -beta, -alpha, level - 1);
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
	PlayerNumber p = (PlayerNumber)((Gomoku::GetInstance()->GetNbMoves() % 2) + 1);
	PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;
	
	pair<int, int> counter = Gomoku::GetInstance()->CounterPairTaking(p, adv);
	if (Gomoku::GetInstance()->GetPlayer(adv)->GetPairs() >= 3 &&
		(counter.first != -1 && counter.second != -1))
	{
		cout << "suce moi en x=" << counter.first << " et en y=" << counter.second << endl;
		Gomoku::GetInstance()->CommitMove(new Move(counter.first, counter.second, p), true);
	}
	else
	{
		QTime chronometer;
		vector<pair<int, int> > covering = Gomoku::GetInstance()->BuildCovering();
		
		this->treeNodes = 0;
		chronometer.start();
		AlgoAlphaBeta(covering, -INFINITY, INFINITY, DEEP_MAX);
		this->time = chronometer.elapsed();
		if (this->bestMove)
		{
			Gomoku::GetInstance()->CommitMove(this->bestMove, true);
			this->bestMove = NULL;
		}
	}
}
