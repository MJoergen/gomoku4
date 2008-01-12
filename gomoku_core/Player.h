#ifndef __PLAYER_H__
# define __PLAYER_H__

typedef enum
{
	IS_HUMAN,
	IS_IA
}	PlayerType;

class Player
{
	private:
		int			movesDone;
		int			pairsCaptured;
		PlayerType	type;

	public:
		Player(PlayerType playerType);
		virtual ~Player() {};

	public:
		void		NewMove();
		int			GetMoves();
		void		NewPairCaptured();
		int			GetPairsCaptured();
		void		SetType(PlayerType playerType);
		PlayerType	GetType();
		void		ResetPlayer();
};

#endif //!__PLAYER_H__