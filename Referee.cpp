#include "Referee.h"

Game_state  Referee::CheckMove(Button ***buttonsArray, Move *move)
{
    if (buttonsArray[move->getX()][move->getY()]->GetState() != NEUTRAL)
        return (FORBIDDEN);
    return (ALLOWED);
}
