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

    this->createPanel(typePanel);

}

void    StatisticsPanel::createPanel(StatisticsPanelType typePanel)
{
    QFont font;
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);

    switch (typePanel)
    {
        case STATS_HUMAN:
            this->groupBox->setTitle("Human");
            this->addInfos(&this->frameNbMoves, &this->hboxLayoutNbMoves,
                           "Nb moves :", &this->nbMoves_t, &this->nbMoves);
            this->addInfos(&this->frameNbPairsTaken, &this->hboxLayoutNbPairsTaken,
                           "Nb pairs taken :", &this->nbPairsTaken_t, &this->nbPairsTaken);
            break;

        case STATS_IA:
            this->groupBox->setTitle("IA");
            this->addInfos(&this->frameNbMoves, &this->hboxLayoutNbMoves,
                           "Nb moves :", &this->nbMoves_t, &this->nbMoves);
            this->addInfos(&this->frameNbPairsTaken, &this->hboxLayoutNbPairsTaken,
                           "Nb pairs taken :", &this->nbPairsTaken_t, &this->nbPairsTaken);
            this->addInfos(&this->frameAlgorythm, &this->hboxLayoutAlgorythm,
                           "Algorithm :", &this->algorithm_t, &this->algorithm);
            this->addInfos(&this->frameNodes, &this->hboxLayoutNodes,
                           "Nodes :", &this->nodes_t, &this->nodes);
            this->addInfos(&this->frameTime, &this->hboxLayoutTime,
                           "Milliseconds :", &this->time_title, &this->time);
            break;
    }
    this->groupBox->setFont(font);
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
    (*title)->setFont(QFont("Sans Serif", 7));
    (*value)->setFont(QFont("Sans Serif", 7));
    (*value)->setAlignment(Qt::AlignRight);
    (*hboxLayout)->addWidget(*title);
    (*hboxLayout)->addWidget(*value);
    this->vboxLayout->addWidget(*frame);
}

void    StatisticsPanel::UpdateStatistics(Player *player)
{
    this->nbMoves->setText(QString("<span style=\" color:#21109b;\">") +
                           QString("%1").arg(player->GetMoves()) + QString("</span>"));
    this->nbPairsTaken->setText(QString("<span style=\" color:#21109b;\">") +
                                QString("%1").arg(player->GetPairs()) + QString("</span>"));
    if (player->GetType() != IS_HUMAN)
    {
        this->algorithm->setText(QString("<span style=\" color:#21109b;\">") +
                                 QString(player->GetType() == IS_IA_ALPHABETA ? "AlphaBeta" : "NegaMax") +
                                 QString("</span>"));
        this->nodes->setText(QString("<span style=\" color:#21109b;\">") +
                             QString("%1").arg(player->GetTreeNodes()) + QString("</span>"));
        this->time->setText(QString("<span style=\" color:#21109b;\">") +
                            QString("%1").arg(player->GetTime()) + QString("</span>"));
    }
}

StatisticsPanel::~StatisticsPanel()
{
    delete this->groupBox;
}
