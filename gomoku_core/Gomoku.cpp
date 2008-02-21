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
	this->doubleThree = true;
	this->alternativeEndGame = true;
	this->ResetGame();
}

// Destructor

Gomoku::~Gomoku()
{
	delete this->players[0];
	delete this->players[1];
	this->deleteBoard();
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

// Game elements setters

void				Gomoku::SetSize(int size)
{
	this->deleteBoard();
    this->size = size;
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

void                Gomoku::SetRules(bool doubleThree, bool alternativeEndGame)
{
    this->doubleThree = doubleThree;
    this->alternativeEndGame = alternativeEndGame;
}

// Public Game methods

MoveActionState		Gomoku::DoNextMove()
{
	int num = this->nextPlayerNum - 1;
	//this->nextPlayerNum = (this->nextPlayerNum == 1) ? 2 : 1;
	if (this->players[num]->GetType() == IS_HUMAN)
		return (WAITING_PLAYER_ACTION);
	else
	{
		IA *ia = (IA*)this->players[num];
		ia->findMove();
		return (DONE);
	}
}

MoveState			Gomoku::CommitMove(Move *move, bool setState)
{
    PlayerNumber p = move->GetPlayerNumber();
	if (p == NEUTRAL)
		p = this->GetPlayerToMove();
	//PlayerNumber p = (PlayerNumber)((this->nb_moves % 2) + 1);
    int x = move->GetX();
    int y = move->GetY();

	MoveState moveState = this->referee.CheckMove(move, this->board, p);

	if (moveState == GOOD_MOVE)
	{
		this->nb_moves++;
		this->stones++;
		board[x][y] = p;
		move->SetPlayerNumber(p);
		this->checkTakenStones(move);
		if (setState)
		{
			this->players[p - 1]->NewMove();
			this->players[p - 1]->CommitPairs();
			this->lastMove = move;
		}
		GameState tmp;

		if ((tmp = this->referee.CheckGame(move, this->players[p - 1], this->stones, this->board)) != IN_PROGRESS)
		{
			this->tmpGameState = tmp;
			if (setState)
				this->gameState = tmp;
		}
//		this->gameState = this->referee.ChecTkGame(move, this->players[p - 1], this->stones, this->board);
		this->nextPlayerNum = (this->nextPlayerNum == 1) ? 2 : 1;
	}
	return (moveState);
}

void				Gomoku::UndoMove(Move *move)
{
	std::list<Point>::iterator it;
	std::list<Point> l = move->GetPointsTaken();
    PlayerNumber p = move->GetPlayerNumber();
	//PlayerNumber p = (PlayerNumber)((this->nb_moves % 2) + 1);
    int x = move->GetX();
    int y = move->GetY();
	PlayerNumber adv = (p == PLAYER1) ? PLAYER2 : PLAYER1;

	this->nb_moves--;
    this->stones--;
	board[x][y] = NEUTRAL;
	move->SetPlayerNumber(NEUTRAL);
	this->players[p - 1]->ResetPendingPairs();
	if (!l.empty())
	{
		for (it = l.begin(); it != l.end(); ++it)
		{
			board[(*it).GetX()][(*it).GetY()] = adv;
			this->stones++;
		}
	}
	this->tmpGameState = IN_PROGRESS;
	this->nextPlayerNum = (this->nextPlayerNum == 1) ? 2 : 1;
}

void				Gomoku::ResetGame()
{
	this->stones = 0;
    this->nb_moves = 0;
	this->gameState = IN_PROGRESS;
	this->tmpGameState = IN_PROGRESS;
	this->nextPlayerNum = 1;
	this->players[0]->ResetPlayer();
	this->players[1]->ResetPlayer();
	this->referee.SetSize(this->size);

	this->board = new unsigned char*[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->board[i] = new unsigned char[this->size];
		for (int j = 0; j < this->size; j++)
			board[i][j] = NEUTRAL;
	}
}

// Private Game methods

void				Gomoku::checkTakenStones(Move *move)
{
	int p = move->GetPlayerNumber();
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

void				Gomoku::deleteBoard()
{
	if (board)
	{
		for (int i = 0; i < this->size; i++)
			delete this->board[i];
		delete this->board;
		this->board = NULL;
	}
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

GameState			Gomoku::GetGameState() const
{
    return (this->gameState);
}

GameState			Gomoku::GetTmpGameState() const
{
    return (this->tmpGameState);
}

unsigned int		Gomoku::GetNbMoves() const
{
	return (this->nb_moves);
}

unsigned char		**Gomoku::GetBoard()
{
	return (this->board);
}

int					Gomoku::GetSize() const
{
	return (this->size);
}

bool                Gomoku::GetRuleDoubleThree() const
{
    return (this->doubleThree);
}

bool                Gomoku::GetRuleAlternativeEndGame() const
{
    return (this->alternativeEndGame);
}

unsigned int	Gomoku::evaluate() const
{
    unsigned int p = (this->nb_moves % 2) + 1;
    unsigned int eval = 0;

    for (int x = 0; x < this->size; x++)
		for (int y = 0; y < this->size; y++)
			if (board[x][y] == p)
				for (unsigned int d = 0; d < 4; d++)
				{
					unsigned int size = 1;
					while (isCorrect(x + (size * dx[d]), y + (size * dy[d]))
						   && (board[x + (size * dx[d])][y + (size * dy[d])] == p))
						size++;
                    eval += size - 1;
                }

    return (eval);
}

vector<pair<int, int> >	Gomoku::BuildCovering()
{
	vector<pair<int, int> > covering;

    for (int x = 0; x < this->size; x++)
		for (int y = 0; y < this->size; y++)
			if (board[x][y] != NEUTRAL)
				for (int size = 1; size < 2; size++)
					for (int d = 0; d < 4; d++)
					{
						if (isCorrect(x + (size * dx[d]), y + (size * dy[d]))
							&& (board[x + (size * dx[d])][y + (size * dy[d])] == NEUTRAL))
							covering.push_back(pair<int, int>(x + (size * dx[d]), y + (size * dy[d])));

						if (isCorrect(x - (size * dx[d]), y - (size * dy[d]))
							&& (board[x - (size * dx[d])][y - (size * dy[d])] == NEUTRAL))
							covering.push_back(pair<int, int>(x - (size * dx[d]), y - (size * dy[d])));
					}
	return (covering);
}

pair<int, int>	Gomoku::CounterPairTaking(PlayerNumber p, PlayerNumber adv)
{
	for (int x = 0; x < this->size; x++)
		for (int y = 0; y < this->size; y++)
			if (board[x][y] == NEUTRAL)
				for (int d = 0; d < 4; d++)
				{
					int size = 1;
					
					if ((isCorrect(x + (size * dx[d]), y + (size * dy[d]))
						&& (board[x + (size * dx[d])][y + (size * dy[d])] == p)) &&
						
						(isCorrect(x + ((size + 1) * dx[d]), y + ((size + 1) * dy[d]))
						&& (board[x + ((size + 1) * dx[d])][y + ((size + 1) * dy[d])] == p)) &&
							
						(isCorrect(x + ((size + 2) * dx[d]), y + ((size + 2) * dy[d]))
						&& (board[x + ((size + 2) * dx[d])][y + ((size + 2) * dy[d])] == adv)))
							return (pair<int, int>(x, y));
							
					if ((isCorrect(x - (size * dx[d]), y - (size * dy[d]))
						&& (board[x - (size * dx[d])][y - (size * dy[d])] == p)) &&
							
						(isCorrect(x - ((size + 1) * dx[d]), y - ((size + 1) * dy[d]))
						&& (board[x - ((size + 1) * dx[d])][y - ((size + 1) * dy[d])] == p)) &&
							
						(isCorrect(x - ((size + 2) * dx[d]), y - ((size + 2) * dy[d]))
						&& (board[x - ((size + 2) * dx[d])][y - ((size + 2) * dy[d])] == adv)))
							return (pair<int, int>(x, y));
				}

	return (pair<int, int>(-1, -1));
}

pair<int, int>	Gomoku::OneMoveWin(PlayerNumber p)
{
	for (int x = 0; x < this->size; x++)
		for (int y = 0; y < this->size; y++)
			if (board[x][y] == NEUTRAL)
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
						return (pair<int, int>(x, y));
				}

	return (pair<int, int>(-1, -1));
}

bool	Gomoku::IsCircled(int x, int y) const
{
	for (int d = 0; d < 4; d++)
	{
		if (isCorrect(x + (1 * dx[d]), y + (1 * dy[d]))
			&& (board[x + (1 * dx[d])][y + (1 * dy[d])] != NEUTRAL))
			return (true);

		if (isCorrect(x - (1 * dx[d]), y - (1 * dy[d]))
			&& (board[x - (1 * dx[d])][y - (1 * dy[d])] != NEUTRAL))
			return (true);
	}
	return (false);
}
