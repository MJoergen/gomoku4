#ifndef _STATISTICSPANEL_H_
# define _STATISTICSPANEL_H_

# include <QLabel>
# include <QFrame>
# include <QGroupBox>
# include <QHBoxLayout>

# include "Mainwindow.h"

class Mainwindow;

class StatisticsPanel
{
    private:
        QLabel      *player;
        QLabel      *algorithm;
        QLabel      *nodes;
        QLabel      *nbFreePions;
        QLabel      *nbMoves;
        QLabel      *player_t;
        QLabel      *algorithm_t;
        QLabel      *nodes_t;
        QLabel      *nbFreePions_t;
        QLabel      *nbMoves_t;
        QFrame      *framePlayer;
        QFrame      *frameAlgorythm;
        QFrame      *frameNodes;
        QFrame      *frameNbFreePions;
        QFrame      *frameNbMoves;
        QHBoxLayout *hboxLayoutPlayer;
        QHBoxLayout *hboxLayoutAlgorythm;
        QHBoxLayout *hboxLayoutNodes;
        QHBoxLayout *hboxLayoutNbFreePions;
        QHBoxLayout *hboxLayoutNbMoves;
        Mainwindow  *mainwindow;
        QGroupBox   *groupBox;

    private:
        void    addInfos(QFrame **frame, QHBoxLayout **hboxLayout,
                         QString titleText, QLabel **title, QLabel **value);

    public:
        StatisticsPanel(Mainwindow *mainwindow);
        ~StatisticsPanel();

    public:
        void    UpdateSize(int nbButtonsSide);
        void    UpdateStatistics(QString player, QString algorithm,
                                 int nbNodes, int nbFreePions, int nbMoves);
};

#endif //!_STATISTICSPANEL_H_
