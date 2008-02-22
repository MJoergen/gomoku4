#include "Referee.h"
#include <sys/time.h>
#include <time.h>
#include <iostream>

using namespace std;

const int	Referee::dx[4] = { 0, -1, -1, -1};
const int	Referee::dy[4] = {-1, -1, 0, 1};

Referee::Referee()
{
	this->freeThreeBorders = new vector<pair<int, int> >();
}

void		Referee::SetSize(int s)
{
    this->size = s;
}

MoveState	Referee::CheckMove(Move *move, unsigned char **board, PlayerNumber p) const
{
	this->freeThreeBorders->clear();
    if (board && move)
    {
        int x = move->GetX();
        int y = move->GetY();

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
                                && (board[x + ((maxf + 1) * dx[d])][y + ((maxf + 1) * dy[d])] == NEUTRAL)
                                && (isCorrect(x - ((4 - maxf) * dx[d]), y - ((4 - maxf) * dy[d])))
                                && (board[x - ((4 - maxf) * dx[d])][y - ((4 - maxf) * dy[d])] == NEUTRAL))
                        {
                            nbFreeThree++;
							this->freeThreeBorders->push_back(pair<int, int>(x + ((maxf + 1) * dx[d]), y + ((maxf + 1) * dy[d])));
							this->freeThreeBorders->push_back(pair<int, int>(x - ((4 - maxf) * dx[d]), y - ((4 - maxf) * dy[d])));
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

GameState	Referee::CheckGame(Move *lastMove, Player *lastPlayer, int stones, unsigned char **board)
{
    if (board && lastMove && lastPlayer)
    {
        int p = lastMove->GetPlayerNumber();

        if (stones == (this->size * this->size))
            return (BOARD_FULL);
        if (lastPlayer->GetPairs() >= NB_PAIRS)
            return ((GameState)p);
        else
        {
            for (int x = 0; x < this->size; x++)
                for (int y = 0; y < this->size; y++)
                {
                    if (board[x][y] == p && !stoneCanBeTaken(x, y, board))
                        for (int d = 0; d < 4; d++)
                        {
                            int forward = 1;
                            while (isCorrect(x + (forward * dx[d]), y + (forward * dy[d]))
                                    && (board[x + (forward * dx[d])][y + (forward * dy[d])] == p)
                                    && (!stoneCanBeTaken(x + (forward * dx[d]), y + (forward * dy[d]), board)))
							{                            
								forward++;
							}

                            int backward = 1;
                            while (isCorrect(x - (backward * dx[d]), y - (backward * dy[d]))
                                    && (board[x - (backward * dx[d])][y - (backward * dy[d])] == p)
                                    && (!stoneCanBeTaken(x - (backward * dx[d]), y - (backward * dy[d]), board)))
							{
								backward++;
							}

                            if (forward + backward > LINE_SIZE)
                            {
                                return ((GameState)p);
                            }
                        }
                }
        }
    }
    return (IN_PROGRESS);
}

vector<pair<int, int> >		*Referee::GetFreeThreeBorders()
{
	return (this->freeThreeBorders);
}

bool		Referee::isCorrect(int x, int y) const
{
    return ((x >= 0) && (y >= 0) && (x < this->size) && (y < this->size));
}

bool		Referee::stoneCanBeTaken(int x, int y, unsigned char **board) const
{
    if (board)
    {
        PlayerNumber p = (PlayerNumber)board[x][y];
        PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;

        for (int d = 0; d < 4; d++)
        {
            if (isCorrect(x + (1 * dx[d]), y + (1 * dy[d]))
                    && (board[x + (1 * dx[d])][y + (1 * dy[d])] == p)
                    && isCorrect(x + (2 * dx[d]), y + (2 * dy[d]))
                    && (board[x + (2 * dx[d])][y + (2 * dy[d])] == adv)
                    && isCorrect(x - (1 * dx[d]), y - (1 * dy[d]))
                    && (board[x - (1 * dx[d])][y - (1 * dy[d])] == NEUTRAL))
            {
                return (true);
            }

            if (isCorrect(x + (1 * dx[d]), y + (1 * dy[d]))
                    && (board[x + (1 * dx[d])][y + (1 * dy[d])] == p)
                    && isCorrect(x + (2 * dx[d]), y + (2 * dy[d]))
                    && (board[x + (2 * dx[d])][y + (2 * dy[d])] == NEUTRAL)
                    && isCorrect(x - (1 * dx[d]), y - (1 * dy[d]))
                    && (board[x - (1 * dx[d])][y - (1 * dy[d])] == adv))
            {
                return (true);
            }

            if (isCorrect(x - (1 * dx[d]), y - (1 * dy[d]))
                    && (board[x - (1 * dx[d])][y - (1 * dy[d])] == p)
                    && isCorrect(x - (2 * dx[d]), y - (2 * dy[d]))
                    && (board[x - (2 * dx[d])][y - (2 * dy[d])] == adv)
                    && isCorrect(x + (1 * dx[d]), y + (1 * dy[d]))
                    && (board[x + (1 * dx[d])][y + (1 * dy[d])] == NEUTRAL))
            {
                return (true);
            }

            if (isCorrect(x - (1 * dx[d]), y - (1 * dy[d]))
                    && (board[x - (1 * dx[d])][y - (1 * dy[d])] == p)
                    && isCorrect(x - (2 * dx[d]), y - (2 * dy[d]))
                    && (board[x - (2 * dx[d])][y - (2 * dy[d])] == NEUTRAL)
                    && isCorrect(x + (1 * dx[d]), y + (1 * dy[d]))
                    && (board[x + (1 * dx[d])][y + (1 * dy[d])] == adv))
            {
                return (true);
            }
        }
    }
    return (false);
}
