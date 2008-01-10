#ifndef _REFEREE_H_
# define _REFEREE_H_

# include "Move.h"
# include "Button.h"
# include "ButtonState.h"

typedef enum
{
    ALLOWED,
    FORBIDDEN,
    VICTORY,
    BOARD_FULL
}   Game_state;

class Referee
{
    public:
        Game_state  CheckMove(Button ***buttonsArray, Move *move);
};

#endif //!_REFEREE_H_
