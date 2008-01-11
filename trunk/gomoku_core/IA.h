#ifndef __IA_H__
# define __IA_H__

# include "Player.h"

class IA : public Player
{
	public:
		IA() : Player(IS_IA) {}

	public:
		virtual void	findMove() = 0;
		virtual ~IA() {};
};

#endif /* __IA_H__ */
