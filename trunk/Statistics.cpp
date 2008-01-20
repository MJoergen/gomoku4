#include "Statistics.h"

Statistics::Statistics(Mainwindow *mainwindow)
{
    this->mainwindow    = mainwindow;
    this->groupBox      = new QGroupBox("Statistics", mainwindow);
    this->vboxLayout    = new QVBoxLayout(this->groupBox);
    this->spacerItem    = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    this->createPanels();
}

void    Statistics::cleanPanels()
{
    this->vboxLayout->removeWidget(this->statisticsPanelPlayer1->GetPanel());
    this->vboxLayout->removeWidget(this->statisticsPanelPlayer2->GetPanel());
    this->vboxLayout->removeItem(this->spacerItem);
    delete this->statisticsPanelPlayer1;
    delete this->statisticsPanelPlayer2;
}

void    Statistics::createPanels()
{
    if (Gomoku::GetInstance()->GetPlayer(PLAYER1)->GetType() == IS_HUMAN)
        this->statisticsPanelPlayer1 = new StatisticsPanel(STATS_HUMAN, this->groupBox);
    else
        this->statisticsPanelPlayer1 = new StatisticsPanel(STATS_IA, this->groupBox);
    if (Gomoku::GetInstance()->GetPlayer(PLAYER2)->GetType() == IS_HUMAN)
        this->statisticsPanelPlayer2 = new StatisticsPanel(STATS_HUMAN, this->groupBox);
    else
        this->statisticsPanelPlayer2 = new StatisticsPanel(STATS_IA, this->groupBox);

    this->vboxLayout->addWidget(this->statisticsPanelPlayer1->GetPanel());
    this->vboxLayout->addWidget(this->statisticsPanelPlayer2->GetPanel());
    this->vboxLayout->addItem(this->spacerItem);
}

void    Statistics::reset()
{
    this->cleanPanels();
    this->createPanels();
}

void    Statistics::UpdateSize(int nbButtonsSide)
{
    this->groupBox->resize(STATS_PANEL_WIDTH,
                           this->mainwindow->height() - MENU_HEIGHT - 3);
    this->groupBox->move(nbButtonsSide * DEFAULT_BUTTONSIZE + 5, MENU_HEIGHT);
}

void    Statistics::UpdateStatistics()
{
    this->reset();
}

Statistics::~Statistics()
{
    delete this->statisticsPanelPlayer1;
    delete this->statisticsPanelPlayer2;
    delete this->vboxLayout;
    delete this->groupBox;
}
