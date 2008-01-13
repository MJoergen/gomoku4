#ifndef _MOVE_H_
# define _MOVE_H_

# include "Point.h"
# include <list>

class Move
{
    private:
        Point					p;
		std::list<Point>		pointsTaken;

    public:
        Move(int _x, int _y);

    public:
        int						GetX() const;
        int						GetY() const;
		std::list<Point>		GetPointsTaken() const;

		void					NewPointTaken(int _x, int _y);
};

#endif //!_MOVE_H_
