#ifndef _REFEREE_H_
# define _REFEREE_H_

# include "Move.h"
# include <vector>

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
		int										size;
		std::vector<std::pair<int, int> >		*freeThreeBorders;
		std::vector<std::pair<int, int> >		linesToCheck;  

    public:
        Referee();

	public:
		void		SetSize(int s);

    public:
        MoveState								CheckMove(Move *move, unsigned char **board, PlayerNumber p, bool doubleThree) const;
        GameState								CheckGame(Move *lastMove, Player *lastPlayer, int stones, unsigned char **board, bool alternativeEndGame);
		std::vector<std::pair<int, int> >		*GetFreeThreeBorders();
		GameState								CheckLinesRegistered(unsigned char **board, bool alternativeEndGame);

	private:
		bool									isCorrect(int x, int y) const;
		bool									stoneCanBeTaken(int x, int y, unsigned char **board) const;
		bool									isValidLine(int x, int y, unsigned char **board, bool alternativeEndGame);
};

#endif //!_REFEREE_H_
