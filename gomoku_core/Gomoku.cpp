#include <cstdlib>
#include "Move.h"
#include "Gomoku.h"
#include "IA_negamax.h"
#include "IA_alphabeta.h"

int     Gomoku::dx[4] = { 0, -1, -1, -1};
int     Gomoku::dy[4] = {-1, -1, 0, 1};
Gomoku  *Gomoku::instance = NULL;

// Constructor

Gomoku::Gomoku() : size(0), board(NULL)
{
	this->lastMove = NULL;
	this->players[0] = new Player(IS_HUMAN);
	this->players[1] = new Player(IS_HUMAN);
	this->ResetGame();
}

// Destructor

Gomoku::~Gomoku()
{
	delete this->players[0];
	delete this->players[1];
	delete this->board;
}

// Singleton methods

Gomoku				*Gomoku::GetInstance()
{
    if (instance == NULL)
        instance = new Gomoku();
    return (instance);
}

void				Gomoku::DestroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}

// Game elements setters (all reset game also)

void				Gomoku::SetSize(int size)
{
    this->size = size;
	this->board = new unsigned char*[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->board[i] = new unsigned char[this->size];
		for (int j = 0; j < this->size; j++)
			board[i][j] = NEUTRAL;
	}
    this->ResetGame();
}

void				Gomoku::SetPlayer(PlayerNumber playerNum, PlayerType type)
{
	if (playerNum != NEUTRAL)
	{
		Player *old = this->players[playerNum - 1];
		switch(type)
		{
			case IS_HUMAN:
				this->players[playerNum - 1] = new Player(IS_HUMAN);
				break;
			case IS_IA_ALPHABETA:
				this->players[playerNum - 1] = new AlphaBeta();
				break;
			case IS_IA_NEGAMAX:
				this->players[playerNum - 1] = new NegaMax();
				break;
		}
		this->players[playerNum - 1]->CopyPlayerStat(old);
		delete old;
	}
}

// Public Game methods

MoveState			Gomoku::DoNextMove()
{
	int num = this->nextPlayerNum - 1;
	this->nextPlayerNum = (this->nextPlayerNum == 1) ? 2 : 1;
	if (this->players[num]->GetType() == IS_HUMAN)
		return (WAITING_PLAYER_ACTION);
	else
	{
		IA *ia = (IA*)this->players[num];
		ia->findMove();
		return (DONE);
	}
}

void				Gomoku::CommitMove(Move *move, bool setState)
{
    int p = GetPlayerToMove();
    int x = move->GetX();
    int y = move->GetY();

    this->nb_moves++;
    this->stones++;
    board[x][y] = p;
	this->checkTakedStones(move, p);
	if (setState)
		this->setMoveState(move);
	this->checkGameState(x, y, p);
}

void				Gomoku::UndoMove(Move *move)
{
	std::list<Point>::iterator it;
	std::list<Point> l = move->GetPointsTaken();
	int adv = (this->GetPlayerToMove() == 1) ? 2 : 1;
	
	this->nb_moves--;
    this->stones--;
	board[move->GetX()][move->GetY()] = NEUTRAL;
	this->players[this->GetPlayerToMove() - 1]->ResetPendingPairs();
	if (!l.empty())
	{
		for (it = l.begin(); it != l.end(); ++it)
		{
			board[(*it).GetX()][(*it).GetY()] = adv;
			this->stones++;
		}
	}
    state = IN_PROGRESS;
}

void				Gomoku::ResetGame()
{
	this->stones = 0;
    this->nb_moves = 0;
	this->state = IN_PROGRESS;
	this->nextPlayerNum = 1;
	this->players[0]->ResetPlayer();
	this->players[1]->ResetPlayer();
}

// Private Game methods

void				Gomoku::checkGameState(unsigned int x, unsigned int y, int p)
{
    if (stones == (this->size * this->size))
        state = BOARD_FULL;
	else if (this->players[p - 1]->GetPairs() >= LINE_SIZE)
		state = (GameState)p;
	else
	{
		for (int d = 0; d < 4; d++)
		{
		    int forward = 1;
		    while (isCorrect(x + (forward * dx[d]), y + (forward * dy[d])) &&
		            (board[x + (forward * dx[d])][y + (forward * dy[d])] == p))
		        forward++;
	
	        int backward = 1;
	        while (isCorrect(x - (backward * dx[d]), y - (backward * dy[d])) &&
	                (board[x - (backward * dx[d])][y - (backward * dy[d])] == p))
	            backward++;
	
	        if (forward + backward > LINE_SIZE)
	            state = (GameState)p;
	    }
	}
}

void				Gomoku::checkTakedStones(Move *move, int p)
{
	int adv = (p == 1) ? 2 : 1;
    unsigned int x = move->GetX();
    unsigned int y = move->GetY();

    for (int d = 0; d < 4; d++)
    {
		if (isCorrect(x + (1 * dx[d]), y + (1 * dy[d]))
			&& (board[x + (1 * dx[d])][y + (1 * dy[d])] == adv)
			&& isCorrect(x + (2 * dx[d]), y + (2 * dy[d]))
			&& (board[x + (2 * dx[d])][y + (2 * dy[d])] == adv)
			&& isCorrect(x + (3 * dx[d]), y + (3 * dy[d]))
			&& (board[x + (3 * dx[d])][y + (3 * dy[d])] == p))
		{
			board[x + (1 * dx[d])][y + (1 * dy[d])] = NEUTRAL;
			board[x + (2 * dx[d])][y + (2 * dy[d])] = NEUTRAL;
			move->NewPointTaken(x + (1 * dx[d]), y + (1 * dy[d]));
			move->NewPointTaken(x + (2 * dx[d]), y + (2 * dy[d]));
			this->stones -= 2;
			this->players[this->GetPlayerToMove() - 1]->NewPairCaptured();
		}

		if (isCorrect(x - (1 * dx[d]), y - (1 * dy[d]))
			&& (board[x - (1 * dx[d])][y - (1 * dy[d])] == adv)
			&& isCorrect(x - (2 * dx[d]), y - (2 * dy[d]))
			&& (board[x - (2 * dx[d])][y - (2 * dy[d])] == adv)
			&& isCorrect(x - (3 * dx[d]), y - (3 * dy[d]))
			&& (board[x - (3 * dx[d])][y - (3 * dy[d])] == p))
		{
			board[x - (1 * dx[d])][y - (1 * dy[d])] = NEUTRAL;
			board[x - (2 * dx[d])][y - (2 * dy[d])] = NEUTRAL;
			move->NewPointTaken(x - (1 * dx[d]), y - (1 * dy[d]));
			move->NewPointTaken(x - (2 * dx[d]), y - (2 * dy[d]));
			this->stones -= 2;
			this->players[this->GetPlayerToMove() - 1]->NewPairCaptured();
		}
	}
}

bool				Gomoku::isCorrect(int x, int y) const
{
    return ((x >= 0) && (y >= 0) && (x < (int)this->size) && (y < (int)this->size));
}

void				Gomoku::setMoveState(Move *move)
{
	this->players[this->GetPlayerToMove() - 1]->NewMove();
	this->players[this->GetPlayerToMove() - 1]->CommitPairs();
	this->lastMove = move;
}

// Game infos getters

PlayerNumber		Gomoku::GetPlayerToMove() const
{
    return ((this->nextPlayerNum == PLAYER1) ? PLAYER2 : PLAYER1);
}

Player				*Gomoku::GetPlayer(PlayerNumber playerNum)
{
	if (playerNum != NEUTRAL)
	{
		return (this->players[playerNum - 1]);
	}
	return (NULL);
}

Move				*Gomoku::GetLastMove()
{
	return (this->lastMove);
}

// A trier !!! :D


GameState Gomoku::getState() const
{
    return (state);
}

std::vector<Move *>	Gomoku::getCorrectMoves() const
{
    std::vector<Move *>	moves;
	unsigned int 		p = GetPlayerToMove();

	if (p == PLAYER1) p = PLAYER2;
	else p = PLAYER1;
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->size; j++)
        {
			bool hasStone = false;
            if (board[i][j] == NEUTRAL)
			{
				if (isCorrect(i + 1, j))
					if (board[i + 1][j] != NEUTRAL)
						hasStone = true;
				if (isCorrect(i - 1, j))
					if (board[i - 1][j] != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i, j + 1))
					if (board[i][j + 1] != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i, j - 1))
					if (board[i][j - 1] != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i + 1, j + 1))
					if (board[i + 1][j + 1] != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i + 1, j - 1))
					if (board[i + 1][j - 1] != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i - 1, j + 1))
					if (board[i - 1][j + 1] != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i - 1, j - 1))
					if (board[i - 1][j - 1] != NEUTRAL)
						hasStone = true;
				if (hasStone) moves.push_back(new Move(i, j));
			}
        }
    return (moves);
}

uint	Gomoku::evaluate() const
{
    unsigned int p = GetPlayerToMove();
    unsigned int eval = 0;

    for (int x = 0; x < this->size; x++)
    {
        for (int y = 0; y < this->size; y++)
        {
            if (board[x][y] == p)
            {
                for (unsigned int d = 0; d < 4; d++)
                {
                    unsigned int size = 1;
                    while (isCorrect(x + (size * dx[d]), y + (size * dy[d]))
                            && (board[x + (size * dx[d])][y + (size * dy[d])] == p))
                        size++;
                    eval += size - 1;
                }
            }
        }
    }
    return (eval);
}
