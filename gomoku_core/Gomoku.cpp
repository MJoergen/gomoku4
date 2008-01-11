#include <cstdlib>
#include "Gomoku.h"
#include "Move.h"
#include "IA_negamax.h"
#include "IA_alphabeta.h"

int     Gomoku::dx[4] = { 0, -1, -1, -1};
int     Gomoku::dy[4] = {-1, -1, 0, 1};
Gomoku  *Gomoku::instance = NULL;

// Constructor

Gomoku::Gomoku() : size(0), board(NULL), algo(ALPHABETA)
{
	this->players[0] = new Player(IS_HUMAN);
	this->players[1] = new AlphaBeta();
	this->ResetGame();
}

// Destructor

Gomoku::~Gomoku()
{
	delete this->players[0];
	delete this->players[1];
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
    this->ResetGame();
}

void				Gomoku::SetPlayer(int playerNum, PlayerType type)
{
	if (playerNum >= 1 && playerNum <= 2)
	{
		delete this->players[playerNum - 1];
		if (type == IS_HUMAN)
			this->players[playerNum - 1] = new Player(IS_HUMAN);
		else
		{
		    switch(this->algo)
			{
				case ALPHABETA:
					this->players[playerNum - 1] = new AlphaBeta();
					break;
				case NEGAMAX:
					this->players[playerNum - 1] = new NegaMax();
					break;
			}
		}
	}
}

void				Gomoku::SetBoard(Button ***board)
{
    this->board = board;
	this->ResetGame();
}

void				Gomoku::SetAlgorithm(AlgorithmType algoType)
{
    this->algo = algoType;

	for (int i = 0; i < 2; i++)
	{
		if (this->players[i]->GetType() == IS_IA)
		{
			delete this->players[i];
		    switch(this->algo)
			{
				case ALPHABETA:
					this->players[i] = new AlphaBeta();
					break;

				case NEGAMAX:
					this->players[i] = new NegaMax();
					break;
			}
		}
	}
	this->ResetGame();
}

// Public Game methods

MoveState			Gomoku::DoNextMove()
{
	while (1)
	{
		int num = this->nextPlayerNum - 1;
		this->nextPlayerNum = (this->nextPlayerNum == 1) ? 2 : 1;
		if (this->players[num]->GetType() == IS_HUMAN)
			return (WAITING_PLAYER_ACTION);
		else
		{
			IA *ia = (IA*)this->players[num];
			ia->findMove();
			if (this->state != IN_PROGRESS)
				return (DONE);
		}
	}
}

unsigned int Gomoku::getPlayerToMove() const
{
    return (nb_moves % 2) + 1;
}

GameState Gomoku::getState() const
{
    return (state);
}

void    Gomoku::ResetGame()
{
	this->stones = 0;
    this->nb_moves = 0;
	this->state = IN_PROGRESS;
	this->nextPlayerNum = 1;
	this->players[0]->ResetPlayer();
	this->players[0]->ResetPlayer();
}

std::vector<Move *>	    Gomoku::initAlgo(unsigned int x) const
{
    std::vector<Move *>	move;

    move.push_back(new Move(this->size / 2 - x, this->size / 2 - x));
    return (move);
}

bool	Gomoku::isCorrect(int x, int y) const
{
    return ((x >= 0) && (y >= 0) && (x < (int)this->size) && (y < (int)this->size));
}

std::vector<Move *>	Gomoku::getCorrectMoves() const
{
    std::vector<Move *>	moves;
	unsigned int 		p = getPlayerToMove();

	if (p == PLAYER1) p = PLAYER2;
	else p = PLAYER1;
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->size; j++)
        {
			bool hasStone = false;
            if (board[i][j]->GetState() == NEUTRAL)
			{
				if (isCorrect(i + 1, j))
					if (board[i + 1][j]->GetState() != NEUTRAL)
						hasStone = true;
				if (isCorrect(i - 1, j))
					if (board[i - 1][j]->GetState()  != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i, j + 1))
					if (board[i][j + 1]->GetState()  != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i, j - 1))
					if (board[i][j - 1]->GetState()  != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i + 1, j + 1))
					if (board[i + 1][j + 1]->GetState()  != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i + 1, j - 1))
					if (board[i + 1][j - 1]->GetState()  != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i - 1, j + 1))
					if (board[i - 1][j + 1]->GetState()  != NEUTRAL)
						hasStone = true;
				if	(isCorrect(i - 1, j - 1))
					if (board[i - 1][j - 1]->GetState()  != NEUTRAL)
						hasStone = true;
				if (hasStone) moves.push_back(new Move(i, j));
			}
        }
    return (moves);
}

int    Gomoku::GetNbMoves()
{
    return (this->nb_moves);
}

void	Gomoku::CheckGameState(unsigned int x, unsigned int y, unsigned int p)
{
    for (uint d = 0; d < 4; d++)
    {
        int forward = 1;
        while (isCorrect(x + (forward * dx[d]), y + (forward * dy[d])) &&
                (board[x + (forward * dx[d])][y + (forward * dy[d])]->GetState() == (int)p))
            forward++;

        int backward = 1;
        while (isCorrect(x - (backward * dx[d]), y - (backward * dy[d])) &&
                (board[x - (backward * dx[d])][y - (backward * dy[d])]->GetState() == (int)p))
            backward++;

        if (forward + backward > LINE_SIZE)
            state = (GameState)p;
    }
    if (stones == (this->size * this->size))
        state = BOARD_FULL;
}

void	         Gomoku::commitMove(const Move *move, bool setState)
{
    unsigned int p = getPlayerToMove();
    unsigned int x = move->getX();
    unsigned int y = move->getY();

    nb_moves++;
    stones++;
    board[x][y]->SetState((buttonState)p);
    if (setState)
        board[x][y]->ChangeState();
	CheckGameState(x, y, p);
}

void	    Gomoku::undoMove(const Move *move)
{
    board[move->getX()][move->getY()]->SetState(NEUTRAL);
    nb_moves--;
    stones--;
    state = IN_PROGRESS;
}

uint	Gomoku::evaluate() const
{
    unsigned int p = getPlayerToMove();
    unsigned int eval = 0;

    for (int x = 0; x < this->size; x++)
    {
        for (int y = 0; y < this->size; y++)
        {
            if (board[x][y]->GetState() == (int)p)
            {
                for (unsigned int d = 0; d < 4; d++)
                {
                    unsigned int size = 1;
                    while (isCorrect(x + (size * dx[d]), y + (size * dy[d]))
                            && (board[x + (size * dx[d])][y + (size * dy[d])]->GetState() == (int)p))
                        size++;
                    eval += size - 1;
                }
            }
        }
    }
    return (eval);
}
