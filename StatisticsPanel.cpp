#include "StatisticsPanel.h"

StatisticsPanel::StatisticsPanel(Mainwindow *mainwindow)
{
    this->mainwindow = mainwindow;
    this->groupBox   = new QGroupBox("Statistics", mainwindow);
    this->vboxLayout    = new QVBoxLayout(this->groupBox);
    this->addInfos(&this->framePlayer, &this->hboxLayoutPlayer, "Player :", &this->player_t, &this->player);
    this->addInfos(&this->frameAlgorythm, &this->hboxLayoutAlgorythm, "Algorithm :", &this->algorithm_t, &this->algorithm);
    this->addInfos(&this->frameNodes, &this->hboxLayoutNodes, "Nodes :", &this->nodes_t, &this->nodes);
    this->addInfos(&this->frameNbFreePions, &this->hboxLayoutNbFreePions, "Free pions :", &this->nbFreePions_t, &this->nbFreePions);
    this->addInfos(&this->frameNbMoves, &this->hboxLayoutNbMoves, "Moves :", &this->nbMoves_t, &this->nbMoves);
    this->vboxLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void    StatisticsPanel::addInfos(QFrame **frame, QHBoxLayout **hboxLayout,
                                  QString titleText, QLabel **title, QLabel **value)
{
    *frame       = new QFrame();
    *hboxLayout  = new QHBoxLayout(*frame);
    *title       = new QLabel(*frame);
    *value       = new QLabel(*frame);

    (*title)->setText(QString("<b>") + titleText + QString("</b>"));
    (*hboxLayout)->addWidget(*title);
    (*hboxLayout)->addWidget(*value);
    this->vboxLayout->addWidget(*frame);
}

void    StatisticsPanel::UpdateSize(int nbButtonsSide)
{
    this->groupBox->resize(STATS_PANEL_WIDTH,
                           this->mainwindow->height() - MENU_HEIGHT - 5);
    this->groupBox->move(nbButtonsSide * DEFAULT_BUTTONSIZE, MENU_HEIGHT);
}

void    StatisticsPanel::UpdateStatistics(QString player, QString algorithm,
                                          int nbNodes, int nbFreePions, int nbMoves)
{
    this->player->setText(player);
    this->algorithm->setText(algorithm);
    this->nodes->setNum(nbNodes);
    this->nbFreePions->setNum(nbFreePions);
    this->nbMoves->setNum(nbMoves);
}

StatisticsPanel::~StatisticsPanel()
{
    delete this->groupBox;
    delete this->algorithm_t;
    delete this->algorithm;
    delete this->frameAlgorythm;
    delete this->hboxLayoutAlgorythm;
    delete this->nodes_t;
    delete this->nodes;
    delete this->frameNodes;
    delete this->hboxLayoutNodes;
    delete this->player_t;
    delete this->player;
    delete this->framePlayer;
    delete this->hboxLayoutPlayer;
    delete this->nbFreePions_t;
    delete this->nbFreePions;
    delete this->frameNbFreePions;
    delete this->hboxLayoutNbFreePions;
    delete this->vboxLayout;
}
