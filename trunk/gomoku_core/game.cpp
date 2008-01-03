#include <cstdlib>

#include "game.h"

Game    *Game::Instance = NULL;

Game::Game() : nb_moves(0), state(0)
{
}

Game    *Game::GetInstance()
{
    if (Instance == NULL)
        Instance = new Game();
    return (Instance);
}

void    Game::IncNbMoves()
{
    this->nb_moves++;
}

void    Game::DecNbMoves()
{
    this->nb_moves--;
}

void    Game::SetState(unsigned int state)
{
    this->state = state;
}

unsigned int	Game::getPlayerToMove() const
{
    return (nb_moves % 2) + 1;
}

unsigned int	Game::getState() const
{
    return state;
}
