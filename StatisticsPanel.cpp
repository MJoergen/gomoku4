#include "StatisticsPanel.h"

StatisticsPanel::StatisticsPanel(StatisticsPanelType typePanel, QGroupBox *parent)
{
    this->parent                = parent;
    this->groupBox              = new QGroupBox(this->parent);
    this->vboxLayout            = new QVBoxLayout(this->groupBox);
    this->algorithm             = NULL;
    this->algorithm_t           = NULL;
    this->frameAlgorythm        = NULL;
    this->hboxLayoutAlgorythm   = NULL;
    this->nodes                 = NULL;
    this->nodes_t               = NULL;
    this->frameNodes            = NULL;
    this->hboxLayoutNodes       = NULL;

    this->vboxLayout->setSpacing(0);

    switch (typePanel)
    {
        case STATS_HUMAN:
            this->groupBox->setTitle("Player");
            this->addInfos(&this->frameNbMoves, &this->hboxLayoutNbMoves,
                           "Moves :", &this->nbMoves_t, &this->nbMoves);
            this->addInfos(&this->frameNbPairsTaken, &this->hboxLayoutNbPairsTaken,
                           "Nb pairs taken :", &this->nbPairsTaken_t, &this->nbPairsTaken);
            this->nbMoves->setNum(0);
            this->nbPairsTaken->setNum(0);
            break;

        case STATS_IA:
            this->groupBox->setTitle("IA");
            this->addInfos(&this->frameNbMoves, &this->hboxLayoutNbMoves,
                           "Moves :", &this->nbMoves_t, &this->nbMoves);
            this->addInfos(&this->frameNbPairsTaken, &this->hboxLayoutNbPairsTaken,
                           "Nb pairs taken :", &this->nbPairsTaken_t, &this->nbPairsTaken);
            this->addInfos(&this->frameAlgorythm, &this->hboxLayoutAlgorythm,
                           "Algorithm :", &this->algorithm_t, &this->algorithm);
            this->addInfos(&this->frameNodes, &this->hboxLayoutNodes,
                           "Nodes :", &this->nodes_t, &this->nodes);
            this->nbMoves->setNum(0);
            this->nbPairsTaken->setNum(0);
            this->algorithm->setText("AlphaBeta");
            this->nodes->setNum(0);
            break;
    }
}

QGroupBox    *StatisticsPanel::GetPanel()
{
    return (this->groupBox);
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

void    StatisticsPanel::UpdateStatistics(Player *player)
{
    this->nbMoves->setNum(player->GetMoves());
    this->nbPairsTaken->setNum(player->GetPairs());
    if (player->GetType() == IS_IA_ALPHABETA || player->GetType() == IS_IA_NEGAMAX)
    {
        this->algorithm->setText(player->GetType() == IS_IA_ALPHABETA ? "AlphaBeta" : "NegaMax");
    }
}

StatisticsPanel::~StatisticsPanel()
{
    delete this->groupBox;
//    delete this->vboxLayout;
//    delete this->nbMoves_t;
//    delete this->nbMoves;
//    delete this->frameNbMoves;
//    delete this->hboxLayoutNbMoves;
//    delete this->nbPairsTaken_t;
//    delete this->nbPairsTaken;
//    delete this->hboxLayoutNbPairsTaken;
//    delete this->frameNbPairsTaken;
//    if (this->algorithm)
//    {
//        delete this->algorithm;
//        delete this->algorithm_t;
//        delete this->frameAlgorythm;
//        delete this->hboxLayoutAlgorythm;
//    }
//    if (this->nodes)
//    {
//        delete this->nbMoves;
//        delete this->nbMoves_t;
//        delete this->frameNbMoves;
//        delete this->hboxLayoutNodes;
//    }
}
