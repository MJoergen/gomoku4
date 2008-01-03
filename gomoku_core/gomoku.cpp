#include "gomoku.h"
#include "Move.h"
#include <cstdlib>

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

Gomoku::Gomoku() : stones(0), nb_moves(0), state(0)
{
    for (unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 0;
    }
}

Gomoku    *Gomoku::GetInstance()
{
  if (Instance == NULL)
    Instance = new Gomoku();
  return (Instance);
}

void		    Gomoku::dump(std::ostream &o) const
{
    const char	symbol[3] = {'.','X','O'};

    for (unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIZE; j++)
            o << symbol[board[i][j]];
        o << std::endl;
    }
}

std::vector<Move *>	    Gomoku::initAlgo(unsigned int x) const
{
    std::vector<Move *>	move;

    move.push_back(new Move(BOARD_SIZE / 2 - x, BOARD_SIZE / 2 - x));
    return (move);
}

bool	Gomoku::isCorrect(int x, int y) const
{
    return ((x >= 0) && (y >= 0) && (x < BOARD_SIZE) && (y < BOARD_SIZE));
}

std::vector<Move *>	Gomoku::getCorrectMoves() const
{
    std::vector<Move *>	moves;

    for (unsigned int i = 0; i < BOARD_SIZE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIZE; j++)
        {
            if (!board[i][j])
                moves.push_back(new Move(i, j));
        }
    }
    return (moves);
}

void	         Gomoku::commitMove(const Move *move)
{
    unsigned int p = getPlayerToMove();
    unsigned int x = move->getX();
    unsigned int y = move->getY();

    nb_moves++;
    stones++;
    board[x][y] = p;
    for (uint d = 0; d < 4; d++)
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
	  state = p;
    }
    if (stones == (BOARD_SIZE * BOARD_SIZE))
        state = FULL_BOARD;
}

void	    Gomoku::undoMove(const Move *move)
{
    board[move->getX()][move->getY()] = 0;
    nb_moves--;
    stones--;
    state = 0;
}

uint	Gomoku::evaluate() const
{
    unsigned int p = getPlayerToMove();
    unsigned int eval = 0;

    for (unsigned int x = 0; x < BOARD_SIZE; x++)
    {
        for (unsigned int y = 0; y < BOARD_SIZE; y++)
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
