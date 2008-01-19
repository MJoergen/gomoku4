#ifndef _STATISTICS_H_
# define _STATISTICS_H_

# include <QLabel>
# include <QFrame>
# include <QGroupBox>
# include <QHBoxLayout>
# include <QVBoxLayout>

# include "StatisticsPanel.h"
# include "Mainwindow.h"

class Mainwindow;

class Statistics
{
    private:
        QVBoxLayout     *vboxLayout;
        Mainwindow      *mainwindow;
        QGroupBox       *groupBox;
        StatisticsPanel *statisticsPanelPlayer1;
        StatisticsPanel *statisticsPanelPlayer2;

    public:
        Statistics(Mainwindow *mainwindow);
        ~Statistics();

    public:
        void    UpdateSize(int nbButtonsSide);
        //void    UpdateStatistics(QString player, QString algorithm, QString mode,
          //                       int nbNodes, int nbFreePions, int nbMoves);
};

#endif //!_STATISTICSPANEL_H_
