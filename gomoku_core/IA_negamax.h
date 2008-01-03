#ifndef __IA_NEGAMAX_H__
# define __IA_NEGAMAX_H__

# include "Move.h"
# include "game.h"
# include "defines.h"

class NegaMax
{
    private:
        unsigned int              treeNodes;
        static const unsigned int DEEP_MAX = 2;

    public:
        int	  AlgoNegaMax(Move **bestMove, int level);
        void  findMove();
};

#endif //!__IA_NEGAMAX_H__
