#include "Statistics.h"

Statistics::Statistics(Mainwindow *mainwindow)
{
    this->mainwindow = mainwindow;
    this->vboxLayout = new QVBoxLayout(this->mainwindow);
    this->groupBox = new QGroupBox("Statistics", mainwindow);

    if (Gomoku::GetInstance()->GetPlayer(PLAYER1)->GetType() == IS_HUMAN)
        this->statisticsPanelPlayer1 = new StatisticsPanel(STATS_HUMAN, this->groupBox);
    else
        this->statisticsPanelPlayer1 = new StatisticsPanel(STATS_IA, this->groupBox);
    if (Gomoku::GetInstance()->GetPlayer(PLAYER2)->GetType() == IS_HUMAN)
        this->statisticsPanelPlayer2 = new StatisticsPanel(STATS_HUMAN, this->groupBox);
    else
        this->statisticsPanelPlayer2 = new StatisticsPanel(STATS_IA, this->groupBox);

    this->vboxLayout->addWidget(this->statisticsPanelPlayer1->GetGroupBox());
    this->vboxLayout->addWidget(this->statisticsPanelPlayer2->GetGroupBox());
    this->vboxLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void    Statistics::UpdateSize(int nbButtonsSide)
{
    this->groupBox->resize(STATS_PANEL_WIDTH,
                           this->mainwindow->height() - MENU_HEIGHT - 3);
    this->groupBox->move(nbButtonsSide * DEFAULT_BUTTONSIZE + 5, MENU_HEIGHT);
}
//
//void    StatisticsPanel::UpdateStatistics(QString player, QString algorithm, QString mode,
//                                          int nbNodes, int nbFreePions, int nbMoves)
//{
//    this->player->setText(player);
//    this->algorithm->setText(algorithm);
//    this->mode->setText(mode);
//    this->nodes->setNum(nbNodes);
//    this->nbFreePions->setNum(nbFreePions);
//    this->nbMoves->setNum(nbMoves);
//}

Statistics::~Statistics()
{
    delete this->statisticsPanelPlayer1;
    delete this->statisticsPanelPlayer2;
    delete this->vboxLayout;
    delete this->groupBox;
}
