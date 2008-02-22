#ifndef _MOVE_H_
# define _MOVE_H_

# include "Point.h"
# include "Player.h"
# include <list>

class Move
{
    private:
        Point					p;
		std::list<Point>		pointsTaken;
		PlayerNumber			playerNumber;

    public:
        Move(int _x, int _y, PlayerNumber playerNum);
        Move(const Move &move);

    public:
        int						GetX() const;
        int						GetY() const;
		PlayerNumber			GetPlayerNumber() const;
		std::list<Point>		GetPointsTaken() const;

	public:
		void					SetPlayerNumber(PlayerNumber num);
		void					NewPointTaken(int _x, int _y);
		void					ResetPointsTaken();
};

#endif //!_MOVE_H_
