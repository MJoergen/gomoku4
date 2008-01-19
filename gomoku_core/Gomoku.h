#ifndef __GOMOKU_H__
# define __GOMOKU_H__

# include <vector>
# include <iostream>
# include "Move.h"
# include "defines.h"
# include "../Button.h"
# include "../AlgorithmType.h"
# include "Player.h"
# include "IA.h"
# include "Point.h"

typedef	enum
{
	IN_PROGRESS,
    VICTORY_PLAYER1,
    VICTORY_PLAYER2,
    ALLOWED,
    FORBIDDEN,
    BOARD_FULL
}	GameState;

typedef enum
{
	WAITING_PLAYER_ACTION,
	DONE
}	MoveState;

class Gomoku
{
    private:
        static				int dx[4];
        static				int dy[4];
        static Gomoku		*instance;

    private:
		int					_x, _y;
        int					size;
		Player				*players[2];
        unsigned char		**board;
        AlgorithmType		algo;

        int					stones;
        unsigned int		nb_moves;
        GameState			state;
		int					nextPlayerNum;



    private:
        Gomoku();
		~Gomoku();

    public:
        static Gomoku       *GetInstance();
        static void         DestroyInstance();

    public:
        void			    SetSize(int size);
		void				SetPlayer(int playerNum, PlayerType type);
        void			    SetAlgorithm(AlgorithmType algo);

	public:
		MoveState			DoNextMove();
		Move				*GetLastMove();
        void				CommitMove(Move *move, bool setState);
        void				UndoMove(Move *move);
        void                ResetGame();

	private:
		void				checkGameState(unsigned int x, unsigned int y, int p);
		void				checkTakedStones(Move *move, int p);
		bool                isCorrect(int x, int y) const;
		void				setMoveState(Move *move);

	public:
		int					GetPlayerToMove() const;

        void	            dump(std::ostream& o) const;
        int                 GetNbMoves();
        unsigned int        evaluate() const;
        GameState        	getState() const;
        std::vector<Move *> getCorrectMoves() const;
        std::vector<Move *> initAlgo(unsigned int x = 0) const;
};

#endif //!__GOMOKU_H__
