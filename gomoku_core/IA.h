#ifndef __IA_H__
# define __IA_H__

# include "Player.h"

class IA : public Player
{
	public:
		IA(PlayerType type) : Player(type) {}
		virtual ~IA() {};

	public:
		virtual void	findMove() = 0;
};

#endif //!__IA_H__
