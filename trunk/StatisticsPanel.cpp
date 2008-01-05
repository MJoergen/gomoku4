#include <iostream>
#include "StatisticsPanel.h"

StatisticsPanel::StatisticsPanel(Mainwindow *mainwindow)
{
    this->mainwindow    = mainwindow;
    this->groupBox      = new QGroupBox("Statistics", mainwindow);
    this->player_t      = new QLabel("Player :", this->groupBox);
    this->player        = new QLabel(this->groupBox);
    this->algorithm_t   = new QLabel("Algorithm :", this->groupBox);
    this->algorithm     = new QLabel(this->groupBox);
    this->nodes_t       = new QLabel("Nodes :", this->groupBox);
    this->nodes         = new QLabel(this->groupBox);
    this->nbFreePions_t = new QLabel("Free pions :", this->groupBox);
    this->nbFreePions   = new QLabel(this->groupBox);
    this->nbMoves_t     = new QLabel("Moves :", this->groupBox);
    this->nbMoves       = new QLabel(this->groupBox);
}

void    StatisticsPanel::UpdateSize(int nbButtonsSide)
{
    this->groupBox->resize(STATS_PANEL_WIDTH,
                           this->mainwindow->height() - MENU_HEIGHT - 5);
    this->groupBox->move(nbButtonsSide * DEFAULT_BUTTONSIZE, MENU_HEIGHT);
    this->player_t->move(5, 20);
    this->player->move(55, 24);
    this->player->resize(100, 10);
    this->algorithm_t->move(5, 40);
    this->algorithm->move(75, 42);
    this->algorithm->resize(100, 15);
    this->nodes_t->move(5, 60);
    this->nodes->move(57, 64);
    this->nodes->resize(100, 10);
    this->nbFreePions_t->move(5, 80);
    this->nbFreePions->move(82, 84);
    this->nbFreePions->resize(100, 10);
    this->nbMoves_t->move(5, 100);
    this->nbMoves->move(55, 104);
    this->nbMoves->resize(100, 10);
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
    delete this->nodes_t;
    delete this->nodes;
    delete this->player_t;
    delete this->player;
    delete this->nbFreePions_t;
    delete this->nbFreePions;
}
