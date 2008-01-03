#ifndef _MOVE_H_
# define _MOVE_H_

class Move
{
    private:
        unsigned int	x, y;

    public:
        Move(unsigned int _x, unsigned int _y);

    public:
        unsigned int	getX() const;
        unsigned int	getY() const;
};

#endif //!_MOVE_H_
