#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QLabel>
# include <QMainWindow>

# include "Button.h"
# include "gomoku.h"
# include "AlgorithmType.h"
# include "OptionsWindow.h"
# include "StatisticsPanel.h"
# include "IA_alphabeta.h"
# include "IA_negamax.h"
# include "IA.h"

# define DEFAULT_BOARDSIZE  5
# define DEFAULT_BUTTONSIZE 50
# define MENU_HEIGHT        25
# define STATS_PANEL_WIDTH  150

class OptionsWindow;
class Alphabeta;
class NegaMax;
class StatisticsPanel;

class Mainwindow : public QMainWindow
{
    Q_OBJECT

    private:
        int                 boardSize;
        bool                iaPlayer;
        IA                  *ia;
        AlgorithmType       algo;
        QMenu               *fileMenu;
        QMenu               *preferenceMenu;
        QAction             *newGameAction;
        QAction             *quitAction;
        QAction             *optionsAction;
        Button              ***buttonsArray;
        OptionsWindow       *optionsWindow;
        StatisticsPanel     *statisticsPanel;
        static Mainwindow   *instance;

    private:
        Mainwindow();
        ~Mainwindow();

    public:
        void               IaPlay();
        void               CreateBoard();
        void               SetBoardSize(int boardSize);
        void               SetAlgorithm(AlgorithmType algo);
        void               UpdateStatistics(int nbConsideredNode);
        static Mainwindow  *GetInstance();
        static void        DestroyInstance();

    private:
        void    init();
        void    doConnects();
        void    setSize();
        void    createMenus();
        void    createIa();
        void    createButtons();
        void    cleanButtonsArray();
        void    moveToCenter();

    public slots:
        void    startNewGame();
        void    showOptionsWindow();
        void    buttonClicked();
};

#endif //!_MAINWINDOW_H_
