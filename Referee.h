#ifndef _REFEREE_H_
# define _REFEREE_H_

# include "Move.h"
# include "Button.h"
# include "gomoku.h"
# include "ButtonState.h"

class Referee
{
    public:
        GameState  CheckMove(Button ***buttonsArray, Move *move);
};

#endif //!_REFEREE_H_
