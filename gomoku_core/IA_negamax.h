#ifndef __IA_NEGAMAX_H__
# define __IA_NEGAMAX_H__

# include "defines.h"
# include "Gomoku.h"
# include "Mainwindow.h"
# include "IA.h"

class Mainwindow;

class NegaMax : public IA
{
    private:
        unsigned int				treeNodes;
        static const unsigned int	DEEP_MAX = 2;
		Move						*bestMove;
		Gomoku						*gomoku;

	public:
		NegaMax();

    public:
        int	  AlgoNegaMax(int level);
        void  findMove();
};

#endif //!__IA_NEGAMAX_H__
