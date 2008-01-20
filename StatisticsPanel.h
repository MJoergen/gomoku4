#ifndef STATISTICSPANEL1_H_
# define STATISTICSPANEL1_H_

# include <QLabel>
# include <QFrame>
# include <QHBoxLayout>
# include <QVBoxLayout>
# include <QGroupBox>

# include "Player.h"

typedef enum
{
    STATS_HUMAN,
    STATS_IA
}   StatisticsPanelType;

class StatisticsPanel
{
    private:
        QLabel              *algorithm_t;
        QLabel              *algorithm;
        QLabel              *nodes_t;
        QLabel              *nodes;
        QLabel              *nbMoves_t;
        QLabel              *nbMoves;
        QLabel              *nbPairsTaken_t;
        QLabel              *nbPairsTaken;
        QFrame              *frameAlgorythm;
        QFrame              *frameNodes;
        QFrame              *frameNbMoves;
        QFrame              *frameNbPairsTaken;
        QHBoxLayout         *hboxLayoutAlgorythm;
        QHBoxLayout         *hboxLayoutNodes;
        QHBoxLayout         *hboxLayoutNbMoves;
        QHBoxLayout         *hboxLayoutNbPairsTaken;
        QVBoxLayout         *vboxLayout;
        QGroupBox           *groupBox;
        QGroupBox           *parent;
        StatisticsPanelType typePanel;

    private:
        void    createPanel(StatisticsPanelType typePanel);
        void    addInfos(QFrame **frame, QHBoxLayout **hboxLayout,
                         QString titleText, QLabel **title, QLabel **value);

    public:
        StatisticsPanel(StatisticsPanelType typePanel, QGroupBox *parent);
        ~StatisticsPanel();

    public:
        QGroupBox   *GetPanel();
        void        UpdateStatistics(Player *player);
};

#endif //!STATISTICSPANEL1_H_
