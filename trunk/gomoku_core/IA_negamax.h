#ifndef __IA_NEGAMAX_H__
#define __IA_NEGAMAX_H__

#include "player.h"
#include "game.h"
#include "defines.h"

class NegaMax : public Player
{
    private:
        uint			treeNodes;
        static const uint	DEEP_MAX = 2;

    public:
        int	AlgoNegaMax(Move **bestMove, int level);
        void  findMove();
};

#endif /* __IA_NEGAMAX_H__ */
