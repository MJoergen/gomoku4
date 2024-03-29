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
        QSpacerItem     *spacerItem;
        StatisticsPanel *statisticsPanelPlayer1;
        StatisticsPanel *statisticsPanelPlayer2;

    private:
        void    cleanPanels();
        void    createPanels();

    public:
        Statistics(Mainwindow *mainwindow);
        ~Statistics();

    public:
        void    Reset();
        void    UpdateSize(int nbButtonsSide);
        void    UpdateStatistics();
};

#endif //!_STATISTICSPANEL_H_
