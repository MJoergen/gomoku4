#include "Referee.h"

const int	Referee::dx[4] = { 0, -1, -1, -1};
const int	Referee::dy[4] = {-1, -1, 0, 1};

Referee::Referee()
{
}

void		Referee::SetSize(int s)
{
	this->size = s;
}

MoveState	Referee::CheckMove(Move *move, unsigned char **board, PlayerNumber p)
{
	if (board && move)
	{
		if (board[move->GetX()][move->GetY()] != NEUTRAL)
			return (NOT_FREE);
	}
	return (GOOD_MOVE);
}

GameState	Referee::CheckGame(Move *lastMove, Player *lastPlayer, int stones, unsigned char **board)
{
	if (board && lastMove && lastPlayer)
	{
		int p = lastMove->GetPlayerNumber();
		int x = lastMove->GetX();
		int y = lastMove->GetY();

		if (stones == (this->size * this->size))
			return (BOARD_FULL);
		if (lastPlayer->GetPairs() >= NB_PAIRS)
			return ((GameState)p);
		else
		{
			for (int d = 0; d < 4; d++)
			{
				int forward = 1;
				while (isCorrect(x + (forward * dx[d]), y + (forward * dy[d]))
					&& (board[x + (forward * dx[d])][y + (forward * dy[d])] == p))
					forward++;
	
				int backward = 1;
				while (isCorrect(x - (backward * dx[d]), y - (backward * dy[d]))
	                && (board[x - (backward * dx[d])][y - (backward * dy[d])] == p))
	            backward++;

				if (forward + backward > LINE_SIZE)
					return ((GameState)p);
			}
	    }
	}
	return (IN_PROGRESS);
}

bool		Referee::isCorrect(int x, int y) const
{
    return ((x >= 0) && (y >= 0) && (x < (int)this->size) && (y < (int)this->size));
}
