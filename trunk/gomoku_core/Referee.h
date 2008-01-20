#ifndef _REFEREE_H_
# define _REFEREE_H_

# include "Move.h"

# define LINE_SIZE	5
# define NB_PAIRS	5

typedef	enum
{
	IN_PROGRESS,
    VICTORY_PLAYER1,
    VICTORY_PLAYER2,
    BOARD_FULL
}	GameState;

typedef enum
{
	GOOD_MOVE,
	NOT_FREE,
	DOUBLE_THREE
}	MoveState;

class Referee
{
	private:
		const static int	dx[4];
		const static int	dy[4];

	private:
		int					size;

    public:
        Referee();

	public:
		void		SetSize(int s);

    public:
        MoveState	CheckMove(Move *move, unsigned char **board, PlayerNumber p);
        GameState	CheckGame(Move *lastMove, Player *lastPlayer, int stones, unsigned char **board);

	private:
		bool		isCorrect(int x, int y) const;
};

#endif //!_REFEREE_H_
