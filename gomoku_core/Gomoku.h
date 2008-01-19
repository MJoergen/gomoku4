#ifndef __GOMOKU_H__
# define __GOMOKU_H__

# include <vector>
# include <iostream>
# include "Move.h"
# include "defines.h"
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
		void				SetPlayer(PlayerNumber playerNum, PlayerType type);

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
		PlayerNumber		GetPlayerToMove() const;
		Player				*GetPlayer(PlayerNumber playerNum);

        void	            dump(std::ostream& o) const;
        unsigned int        evaluate() const;
        GameState        	getState() const;
        std::vector<Move *> getCorrectMoves() const;
};

#endif //!__GOMOKU_H__
