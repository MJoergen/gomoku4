#include "Player.h"

Player::Player(PlayerType playerType) : movesDone(0), pairsCaptured(0), type(playerType)
{
}

void		Player::NewMove()
{
	this->movesDone++;
}

int			Player::GetMoves()
{
	return (this->movesDone);
}

void		Player::NewPairCaptured()
{
	this->pairsCaptured++;
}

int			Player::GetPairsCaptured()
{
	return (this->pairsCaptured);
}

void		Player::SetType(PlayerType playerType)
{
	this->type = playerType;
}

PlayerType	Player::GetType()
{
	return (this->type);
}

void		Player::ResetPlayer()
{
	this->movesDone = 0;
	this->pairsCaptured = 0;
}
