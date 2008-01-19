#ifndef __PLAYER_H__
# define __PLAYER_H__

typedef enum
{
	IS_HUMAN,
	IS_IA_ALPHABETA,
	IS_IA_NEGAMAX
}	PlayerType;

typedef enum
{
    NEUTRAL,
    PLAYER1,
    PLAYER2
}   PlayerNumber;

class Player
{
	private:
		int			movesDone;
		int			pairsCaptured;
		int			pendingPairs;
		PlayerType	type;

	public:
		Player(PlayerType playerType);
		virtual ~Player() {};

	public:
		void		NewMove();
		int			GetMoves();
		void		NewPairCaptured();
		int			GetPairs();
		void		ResetPendingPairs();
		void		CommitPairs();
		int			GetPairsCaptured();
		void		SetType(PlayerType playerType);
		PlayerType	GetType();
		void		CopyPlayerStat(Player *player);
		void		ResetPlayer();
};

#endif //!__PLAYER_H__
