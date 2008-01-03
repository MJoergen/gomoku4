#ifndef __IA_ALPHABETA_H__
# define __IA_ALPHABETA_H__

# include "Move.h"
# include "game.h"
# include "defines.h"

class AlphaBeta
{
    private:
        unsigned int			    treeNodes;
        static const unsigned int	DEEP_MAX = 3;

    public:
        int	    AlgoAlphaBeta(Move **bestMove, int alpha, int beta, int level);
        void    findMove();
};

#endif //!__IA_ALPHABETA_H__
