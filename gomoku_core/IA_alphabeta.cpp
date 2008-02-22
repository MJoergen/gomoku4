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

int		AlphaBeta::AlgoAlphaBeta(vector<pair<int, int> > *covering, int alpha, int beta, int level)
{
    this->treeNodes++;

	if (Gomoku::GetInstance()->GetTmpGameState() == BOARD_FULL)
		return (0);
	else if (Gomoku::GetInstance()->GetTmpGameState() != IN_PROGRESS)
		return (-INFINITY);
    if (!level)
        return (-(this->gomoku->evaluate()));

	int val;
	vector<pair<int, int> >::iterator it = covering->begin();
	vector<pair<int, int> >::iterator eit = covering->end();

	for (; it != eit; it++)
	{
		Move move(it->first, it->second, (PlayerNumber)((this->gomoku->GetNbMoves() % 2) + 1));

		if (this->gomoku->CommitMove(&move, false) == GOOD_MOVE)
		{
			val = -AlgoAlphaBeta(covering, -beta, -alpha, level - 1);
			this->gomoku->UndoMove(&move);
			if (val > alpha)
			{
				alpha = val;
				if (this->bestMove)
					delete this->bestMove;
				this->bestMove = new Move(move);
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
	pair<int, int> CounterPair = Gomoku::GetInstance()->CounterPairTaking(p, adv);
	pair<int, int> oneMove = Gomoku::GetInstance()->OneMoveWin(p);
	vector<pair<int, int> > *ThreeBorders = Gomoku::GetInstance()->GetFreeThreeBorders();

	if (!ThreeBorders->empty())
	{
		pair<int, int> CounterThree = (*ThreeBorders)[0];
		Gomoku::GetInstance()->CommitMove(new Move(CounterThree.first, CounterThree.second, p), true);
	}
	else if (Gomoku::GetInstance()->GetPlayer(adv)->GetPairs() >= 3 &&
		(CounterPair.first != -1 && CounterPair.second != -1))
	{
		Gomoku::GetInstance()->CommitMove(new Move(CounterPair.first, CounterPair.second, p), true);
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
		AlgoAlphaBeta(covering, -INFINITY, INFINITY, DEEP_MAX);
		this->time = chronometer.elapsed();
		if (this->bestMove)
		{
			Gomoku::GetInstance()->CommitMove(new Move(this->bestMove->GetX(), this->bestMove->GetY(), p), true);
			this->bestMove = NULL;
		}
		else
				std::cout << "Oh Jason fait du caca..." << std::endl;
	}
}
