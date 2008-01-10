#include "Referee.h"

GameState  Referee::CheckMove(Button ***buttonsArray, Move *move)
{
    if (buttonsArray[move->getX()][move->getY()]->GetState() != NEUTRAL)
        return (FORBIDDEN);
    return (ALLOWED);
}

/*GameState  Referee::CheckGame()
{
    if (Gomoku::GetInstance()->getState() == )
}*/
