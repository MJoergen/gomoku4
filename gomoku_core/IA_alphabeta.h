#ifndef __IA_ALPHABETA_H__
# define __IA_ALPHABETA_H__

# include "defines.h"
# include "Gomoku.h"
# include "Mainwindow.h"
# include "IA.h"

class Mainwindow;

class AlphaBeta : public IA
{
    private:
        unsigned int				treeNodes;
        static const unsigned int	DEEP_MAX = 3;
		Move						*bestMove;
		Gomoku						*gomoku;

	public:
		AlphaBeta();

	public:
        int	AlgoAlphaBeta(int alpha, int beta, int level);
        void findMove();
};

#endif //!__IA_ALPHABETA_H__
