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

using namespace std;

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
		bool                doubleThree;
		bool                alternativeEndGame;
		Player				*players[2];
        unsigned char		**board;
		Referee				referee;

        int					stones;
        unsigned int		nb_moves;
        GameState			gameState;
		GameState			tmpGameState;
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
		void                SetRules(bool doubleThree, bool alternativeEndGame);

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
		GameState			GetTmpGameState() const;
		bool                GetRuleDoubleThree() const;
		bool                GetRuleAlternativeEndGame() const;
		unsigned int		GetNbMoves() const;
        unsigned char		**GetBoard();
		int					GetSize() const;

        unsigned int        evaluate() const;
		void				BuildCovering(vector<pair<int, int> > *covering, PlayerNumber adv);
		pair<int, int>		CounterPairTaking(PlayerNumber p, PlayerNumber adv);
		pair<int, int>		OneMoveWin(PlayerNumber p);
		bool				IsCircled(int x, int y) const;
		vector<pair<int, int> >	*GetFreeThreeBorders();
};

#endif //!__GOMOKU_H__
