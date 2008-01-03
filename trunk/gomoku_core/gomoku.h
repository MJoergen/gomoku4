#ifndef __GOMOKU_H__
# define __GOMOKU_H__

# include <vector>
# include <iostream>
# include "Move.h"
# include "defines.h"
# include "../Button.h"
# include "../AlgorithmType.h"

class Gomoku
{
    private:
        static	 int dx[4];
        static	 int dy[4];
        static  Gomoku    *Instance;

        unsigned int    stones;
        unsigned int	nb_moves;
        unsigned int	state;
	unsigned int	size;
	Button		**board;
	AlgorithmType	AlgoType;
	

    public:
        Gomoku();

    public:
        bool                    isCorrect(int x, int y) const;
        void	                dump(std::ostream& o) const;
	void			SetSize(unsigned int size);
	void			SetAlgorithm(AlgorithmType algo);
	void			SetBoard(Button **button);
        unsigned int            evaluate() const;
        std::vector<Move *>  getCorrectMoves() const;
        std::vector<Move *>  initAlgo(unsigned int x = 0) const;

        static Gomoku  *GetInstance();
        unsigned int getPlayerToMove() const;
        unsigned int getState() const;

    public:

        void	commitMove(const Move *move);
        void	undoMove(const Move *move);

};

#endif //!__GOMOKU_H__
