#include <iostream>
#include "gomoku.h"
#include "IA_alphabeta.h"
#include "IA_negamax.h"

using namespace std;

int	 main(void)
{
  IA	*player1 = new AlphaBeta();
  IA	*player2 = new NegaMax();

    player1->findMove();
    //Gomoku::GetInstance()->dump(cout);
    while (!Gomoku::GetInstance()->getState())
    {
        player2->findMove();
	//Gomoku::GetInstance()->dump(cout);
        if (Gomoku::GetInstance()->getState())
            break;
        player1->findMove();
	//Gomoku::GetInstance()->dump(cout);
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
