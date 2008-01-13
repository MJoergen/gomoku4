#include "Point.h"

Point::Point(int _x, int _y) : x(_x), y(_y)
{
}

int		Point::GetX() const
{
    return x;
}

int		Point::GetY() const
{
    return y;
}
