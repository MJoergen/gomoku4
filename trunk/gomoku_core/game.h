#ifndef __GAME_H__
# define __GAME_H__

class	Game
{
    protected:
        unsigned int	nb_moves;
        unsigned int	state;

    private:
        static  Game    *Instance;

    private:
        Game();

    public:
        static Game  *GetInstance();
        unsigned int getPlayerToMove() const;
        unsigned int getState() const;
};

#endif //!__GAME_H__
