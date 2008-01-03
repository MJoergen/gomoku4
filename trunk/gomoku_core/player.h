#ifndef __PLAYER_H__
# define __PLAYER_H__

# include "move.h"

class	Player
{
    public:
        virtual void findMove() = 0;
        virtual ~Player() {}
};

#endif //!__PLAYER_H__
