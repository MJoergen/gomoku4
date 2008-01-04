#include <cstdlib>
#include <iostream>
#include "gomoku.h"
#include "Move.h"

int Gomoku::dx[4] = { 0,-1,-1,-1};
int Gomoku::dy[4] = {-1,-1, 0, 1};

Gomoku    *Gomoku::Instance = NULL;

unsigned int Gomoku::getPlayerToMove() const
{
  return (nb_moves % 2) + 1;
}

unsigned int Gomoku::getState() const
{
  return (state);
}

void    Gomoku::IncMove()
{
    this->nb_moves++;
}

Gomoku::Gomoku() : stones(0), nb_moves(0), state(0)
{
}

void	Gomoku::SetSize(unsigned int size)
{
  this->size = size;
}

void	Gomoku::SetAlgorithm(AlgorithmType algo)
{
  this->AlgoType = algo;
}

void	Gomoku::SetBoard(Button **board)
{
  this->board = board;
}

Gomoku    *Gomoku::GetInstance()
{
  if (Instance == NULL)
    Instance = new Gomoku();
  return (Instance);
}

/*void		    Gomoku::dump(std::ostream &o) const
{
  const char	symbol[3] = {'.','X','O'};

    for (unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIZE; j++)
            o << symbol[board[i][j]];
        o << std::endl;
	}
}*/

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

    for (unsigned int i = 0; i < this->size; i++)
    {
        for (unsigned int j = 0; j < this->size; j++)
        {
			if (board[i][j].GetState() == NEUTRAL)
			{
				std::cout << i << " " << j << std::endl;
                moves.push_back(new Move(i, j));
			}
        }
    }
    return (moves);
}

void	         Gomoku::commitMove(const Move *move, bool setState)
{
    unsigned int p = getPlayerToMove();
    unsigned int x = move->getX();
    unsigned int y = move->getY();

    nb_moves++;
    stones++;
	board[x][y].SetState((buttonState)p);
	if (setState)
		board[x][y].ChangeState();
    for (uint d = 0; d < 4; d++)
    {
        int forward = 1;
        while (isCorrect(x + (forward * dx[d]), y + (forward * dy[d])) &&
               (board[x + (forward * dx[d])][y + (forward * dy[d])].GetState() == (int)p))
            forward++;

        int backward = 1;
        while (isCorrect(x - (backward * dx[d]), y - (backward * dy[d])) &&
               (board[x - (backward * dx[d])][y - (backward * dy[d])].GetState() == (int)p))
            backward++;

        if (forward + backward > LINE_SIZE)
	  state = p;
    }
    if (stones == (this->size * this->size))
        state = FULL_BOARD;
}

void	    Gomoku::undoMove(const Move *move)
{
    board[move->getX()][move->getY()].SetState(NEUTRAL);
    nb_moves--;
    stones--;
    state = 0;
}

uint	Gomoku::evaluate() const
{
    unsigned int p = getPlayerToMove();
    unsigned int eval = 0;
    std::cout << p << std::endl;
    for (unsigned int x = 0; x < this->size; x++)
    {
        for (unsigned int y = 0; y < this->size; y++)
        {
            if (board[x][y].GetState() == (int)p)
            {
                for (unsigned int d = 0; d < 4; d++)
                {
                    unsigned int size = 1;
                    while (isCorrect(x + (size * dx[d]), y + (size * dy[d]))
                            && (board[x + (size * dx[d])][y + (size * dy[d])].GetState() == (int)p))
                        size++;
                    eval += size - 1;
                }
            }
        }
    }
    return (eval);
}
