#include <iostream>
#include "gomoku.h"
#include "IA_alphabeta.h"
//#include "IA_negamax.h"

using namespace std;

int	 main(void)
{
  AlphaBeta *player1 = new AlphaBeta();
  AlphaBeta *player2 = new AlphaBeta();

    player1->findMove();
    while (!Gomoku::GetInstance()->getState())
    {
        player2->findMove();
        if (Gomoku::GetInstance()->getState())
            break;
        player1->findMove();
    }

    cout << "Winner: ";
    if (Gomoku::GetInstance()->getState() == FULL_BOARD)
        cout << "None" << endl;
    else
        cout << "Player " << Gomoku::GetInstance()->getState() << endl;

    delete player1;
    delete player2;
    return (0);
}
