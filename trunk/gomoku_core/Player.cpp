#include "Player.h"

Player::Player(PlayerType playerType) : movesDone(0), pairsCaptured(0), pendingPairs(0), type(playerType)
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
	this->pendingPairs++;
}

int			Player::GetPairs()
{
	return (this->pairsCaptured + this->pendingPairs);
}

void		Player::ResetPendingPairs()
{
	this->pendingPairs = 0;
}

void		Player::CommitPairs()
{
	this->pairsCaptured += this->pendingPairs;
	this->pendingPairs = 0;
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

void		Player::CopyPlayerStat(Player *player)
{
	this->movesDone = player->GetMoves();
	this->pairsCaptured = player->GetPairsCaptured();
	this->pendingPairs = player->GetPairs() - this->pairsCaptured;
}

void		Player::ResetPlayer()
{
	this->movesDone = 0;
	this->pairsCaptured = 0;
}
