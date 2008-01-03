/*#include "IA_negamax.h"

int	NegaMax::AlgoNegaMax(Move **bestMove, int level)
{
  treeNodes++;
  *bestMove = NULL;
  
  if (game->getState() == FULL_BOARD)
    return (0);
  else if (game->getState())
    return (-INFINITY);
  if (!level)
    return (-(game->evaluate()));
  
  vector<Move *> moves = game->getCorrectMoves();
  Move *child;
  int best, val;
  
  *bestMove = moves[0];
  best = -INFINITY;
  vector<Move *>::iterator it = moves.begin();
  vector<Move *>::iterator eit = moves.end();

  for (; it != eit; it++)
    {
      game->commitMove(*it);
      val = -AlgoNegaMax(&child, level - 1);
      if (child)
	delete child;
      game->undoMove(*it);
      if (val > best)
	{
	  best = val;
	  *bestMove = *it;
	}
    }
  for (it = moves.begin(); it != eit; it++)
    if (*it != *bestMove)
      delete *it;
  return (best);
}

Move	*NegaMax::findMove()
{
  Move *bestMove;
  treeNodes = 0;
  AlgoNegaMax(&bestMove, DEEP_MAX);
  cout << "<< negamax >>" << endl << "noeuds : " << treeNodes << endl;
  return (bestMove);
}

Move	*NegaMax::makeMove(const Move *opponent)
{
  if (opponent)
    {
      Move *move;
      game->commitMove(opponent);
      move = findMove();
      game->commitMove(move);
      return (move);
    }
  else
    {
      vector<Move *>	onemove;
      onemove = game->initAlgo();
      vector<Move*>::iterator it = onemove.begin();
      game->commitMove(*it);
      return (*it);
    }
}
*/
