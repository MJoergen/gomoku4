#ifndef _MOVE_H_
# define _MOVE_H_

class Move
{
    private:
        int	x, y;

    public:
        Move(int _x, int _y);

    public:
        int	getX() const;
        int	getY() const;
};

#endif //!_MOVE_H_
