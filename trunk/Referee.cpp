#include <QMessageBox>

#include "Referee.h"

Referee::Referee(Mainwindow *mainwindow)
{
    this->mainwindow = mainwindow;
}

GameState  Referee::CheckMove(Button ***buttonsArray, Move *move)
{
    if (buttonsArray[move->getX()][move->getY()]->GetState() != NEUTRAL)
    {
        QMessageBox::critical(this->mainwindow, "Gomoku - Illegal action",
                              "This pion is not free. You are allowed to use it.");
        return (FORBIDDEN);
    }
    return (ALLOWED);
}

GameState  Referee::CheckGame()
{
    switch (Gomoku::GetInstance()->getState())
    {
        case VICTORY_PLAYER1 :
            QMessageBox::information(this->mainwindow, "Gomoku - Game information",
                                     "Congratulation. You win !");
            return (VICTORY_PLAYER1);

        case VICTORY_PLAYER2 :
            QMessageBox::information(this->mainwindow, "Gomoku - Game information",
                                     "Artifial intelligence beat you !");
            return (VICTORY_PLAYER2);

        case BOARD_FULL :
            QMessageBox::information(this->mainwindow, "Gomoku - Game information",
                                     "The board is full.\nA new game is being to start.");
            return (BOARD_FULL);

        default : return (IN_PROGRESS);
    }
}
