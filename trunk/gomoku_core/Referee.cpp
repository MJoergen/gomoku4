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

MoveState	Referee::CheckMove(Move *move, unsigned char **board, PlayerNumber p) const
{
	if (board && move)
	{
		int x = move->GetX();
		int y = move->GetY();
		PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;

		if (board[x][y] != NEUTRAL)
			return (NOT_FREE);
		else
		{
			int nbFreeThree = 0;
			for (int d = 0; d < 4; d++)
			{
				for (int maxf = 0; maxf < 4; maxf++)
				{
					int nbPlayerStones = 0;
					int nbNeutralStones = 0;
					bool hasAdvStones = false;

					for (int forward = 1; forward <= maxf; forward++)
					{
						if (isCorrect(x + (forward * dx[d]), y + (forward * dy[d])))
						{
							PlayerNumber state = (PlayerNumber)board[x + (forward * dx[d])][y + (forward * dy[d])];
							if (state == NEUTRAL)
								nbNeutralStones++;
							else if (state == p)
								nbPlayerStones++;
							else
							{
								hasAdvStones = true;
								break;
							}
						}
					}

					for (int backward = 1; backward <= 3 - maxf && !hasAdvStones; backward++)
					{
						if (isCorrect(x - (backward * dx[d]), y - (backward * dy[d])))
						{
							PlayerNumber state = (PlayerNumber)board[x - (backward * dx[d])][y - (backward * dy[d])];
							if (state == NEUTRAL)
								nbNeutralStones++;
							else if (state == p)
								nbPlayerStones++;
							else
							{
								hasAdvStones = true;
								break;
							}
						}
					}

					if (!hasAdvStones && nbPlayerStones == 2 && nbNeutralStones == 1)
					{
						if ((isCorrect(x + ((maxf + 1) * dx[d]), y + ((maxf + 1) * dy[d])))
							&& (board[x + ((maxf + 1) * dx[d])][y + ((maxf + 1) * dy[d])] != adv)
							&& (isCorrect(x - ((4 - maxf) * dx[d]), y - ((4 - maxf) * dy[d])))
							&& (board[x - ((4 - maxf) * dx[d])][y - ((4 - maxf) * dy[d])] != adv))
						{
							nbFreeThree++;
							break;
						}
					}
				}
				if (nbFreeThree > 1)
					return (DOUBLE_THREE);
			}
		}
	}
	return (GOOD_MOVE);
}

GameState	Referee::CheckGame(Move *lastMove, Player *lastPlayer, int stones, unsigned char **board) const
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
    return ((x >= 0) && (y >= 0) && (x < this->size) && (y < this->size));
}

bool		Referee::stoneCanBeTaken(Move *move, unsigned char **board) const
{
	if (board && move)
	{
		int x = move->GetX();
		int y = move->GetY();
		PlayerNumber p = move->GetPlayerNumber();
		PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;
		

	}
}
