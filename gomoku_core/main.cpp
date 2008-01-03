#include <iostream>
#include "game.h"
#include "player.h"
#include "gomoku.h"
#include "IA_alphabeta.h"
//#include "IA_negamax.h"

using namespace std;

int	 main(void)
{
    Player *player1 = new AlphaBeta();
    Player *player2 = new AlphaBeta();

    player1->findMove();
    while (!Game::GetInstance()->getState())
    {
        player2->findMove();
        if (Game::GetInstance()->getState())
            break;
        player1->findMove();
    }

    cout << "Winner: ";
    if (Game::GetInstance()->getState() == FULL_BOARD)
        cout << "None" << endl;
    else
        cout << "Player " << Game::GetInstance()->getState() << endl;

    delete player1;
    delete player2;
    return (0);
}
