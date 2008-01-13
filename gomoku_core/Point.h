#ifndef _POINT_H_
# define _POINT_H_

class Point
{
    private:
        int	x, y;

    public:
        Point(int _x, int _y);

    public:
        int	GetX() const;
        int	GetY() const;
};

#endif //!_POINT_H_
