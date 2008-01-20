#ifndef __GOMOKU_H__
# define __GOMOKU_H__

# include <vector>
# include <iostream>
# include "Move.h"
# include "defines.h"
# include "Player.h"
# include "IA.h"
# include "Point.h"
# include "Referee.h"

typedef enum
{
	WAITING_PLAYER_ACTION,
	DONE,
	GAME_FINISHED
}	MoveActionState;

class Gomoku
{
	private:
        static				int dx[4];
        static				int dy[4];
        static Gomoku		*instance;

    private:
		Move				*lastMove;
		int					size;
		Player				*players[2];
        unsigned char		**board;
		Referee				referee;

        int					stones;
        unsigned int		nb_moves;
        GameState			gameState;
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
		MoveActionState		DoNextMove();
        MoveState			CommitMove(Move *move, bool setState);
        void				UndoMove(Move *move);
        void                ResetGame();

	private:
		void				checkTakenStones(Move *move);
		bool                isCorrect(int x, int y) const;
		void				deleteBoard();

	public:
		PlayerNumber		GetPlayerToMove() const;
		Player				*GetPlayer(PlayerNumber playerNum);
		Move				*GetLastMove();
        GameState        	GetGameState() const;

        void	            dump(std::ostream& o) const;
        unsigned int        evaluate() const;
        std::vector<Move *> getCorrectMoves() const;
};

#endif //!__GOMOKU_H__
