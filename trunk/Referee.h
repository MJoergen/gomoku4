#ifndef _REFEREE_H_
# define _REFEREE_H_

# include "Mainwindow.h"

class Mainwindow;

class Referee
{
    private:
        Mainwindow  *mainwindow;

    public:
        Referee(Mainwindow *mainwindow);

    public:
        GameState  CheckMove(Button ***buttonsArray, Move *move);
        GameState  CheckGame();
};

#endif //!_REFEREE_H_
