#include "Move.h"

Move::Move(int _x, int _y) : x(_x), y(_y)
{
}

int Move::getX() const
{
    return x;
}

int Move::getY() const
{
    return y;
}
