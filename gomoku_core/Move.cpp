#include "Move.h"

Move::Move(int _x, int _y, PlayerNumber playerNum) : p(_x, _y), playerNumber(playerNum)
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

PlayerNumber		Move::GetPlayerNumber() const
{
	return (this->playerNumber);
}

std::list<Point>	Move::GetPointsTaken() const
{
	return (this->pointsTaken);
}

void				Move::SetPlayerNumber(PlayerNumber num)
{
	this->playerNumber = num;
}

void				Move::NewPointTaken(int _x, int _y)
{
	this->pointsTaken.push_back(Point(_x, _y));
}
