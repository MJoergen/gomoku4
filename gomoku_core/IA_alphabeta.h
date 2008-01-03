#ifndef __IA_ALPHABETA_H__
#define __IA_ALPHABETA_H__

#include "player.h"
#include "game.h"
#include "defines.h"

class AlphaBeta : public Player
{
 private:
  uint			treeNodes;
  static const uint	DEEP_MAX = 3;
  
 public:
  int	AlgoAlphaBeta(Move **bestMove, int alpha, int beta, int level);
  void  findMove();
};

#endif /* __IA_ALPHABETA_H__ */
