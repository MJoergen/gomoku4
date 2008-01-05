#ifndef _STATISTICSPANEL_H_
# define _STATISTICSPANEL_H_

# include <QLabel>
# include <QGroupBox>

# include "Mainwindow.h"

class Mainwindow;

class StatisticsPanel
{
    private:
        QLabel      *player_t;
        QLabel      *player;
        QLabel      *algorithm_t;
        QLabel      *algorithm;
        QLabel      *nodes_t;
        QLabel      *nodes;
        QLabel      *nbFreePions_t;
        QLabel      *nbFreePions;
        QLabel      *nbMoves_t;
        QLabel      *nbMoves;
        Mainwindow  *mainwindow;
        QGroupBox   *groupBox;

    public:
        StatisticsPanel(Mainwindow *mainwindow);
        ~StatisticsPanel();

    public:
        void    UpdateSize(int nbButtonsSide);
        void    UpdateStatistics(QString player, QString algorithm,
                                 int nbNodes, int nbFreePions, int nbMoves);
};

#endif //!_STATISTICSPANEL_H_
