#include "Move.h"

Move::Move(unsigned int _x, unsigned int _y) : x(_x), y(_y)
{
}

unsigned int    Move::getX() const
{
    return x;
}

unsigned int	Move::getY() const
{
    return y;
}
