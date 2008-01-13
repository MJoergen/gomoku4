#include "Move.h"

Move::Move(int _x, int _y) : p(_x, _y)
{
}

int					Move::GetX() const
{
    return (this->p.GetX());
}

int					Move::GetY() const
{
    return (this->p.GetY());
}

std::list<Point>	Move::GetPointsTaken() const
{
	return (this->pointsTaken);
}

void				Move::NewPointTaken(int _x, int _y)
{
	this->pointsTaken.push_back(Point(_x, _y));
}
