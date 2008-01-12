#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QLabel>
# include <QMainWindow>

# include "IA.h"
# include "Button.h"
# include "Gomoku.h"
# include "Referee.h"
# include "ModesWindow.h"
# include "AlgorithmType.h"
# include "OptionsWindow.h"
# include "StatisticsPanel.h"
# include "ButtonIconFactory.h"

# define DEFAULT_BOARDSIZE  5
# define DEFAULT_BUTTONSIZE 50
# define MENU_HEIGHT        25
# define STATS_PANEL_WIDTH  190

class OptionsWindow;
class Alphabeta;
class NegaMax;
class StatisticsPanel;
class Referee;

class Mainwindow : public QMainWindow
{
    Q_OBJECT

	private:
        static Mainwindow   *instance;

	private:
        QMenu               *fileMenu;
        QMenu               *preferenceMenu;
        QAction             *newGameAction;
        QAction             *quitAction;
        QAction             *optionsAction;
        QAction             *modesAction;

    private:
        int                 boardSize;
        Mode                mode;
        AlgorithmType       algo;
        Button              ***buttonsArray;
        Referee             *referee;
        StatisticsPanel     *statisticsPanel;
		MoveState			moveState;

    private:
        Mainwindow();
        ~Mainwindow();

	public:
        static Mainwindow  *GetInstance();
        static void        DestroyInstance();

    public:
        void               CreateBoard();
        void               SetBoardSize(int boardSize);
        void               SetAlgorithm(AlgorithmType algo);
        void               UpdateStatistics(int nbConsideredNode);

    private:
        void				init();
        void				doConnects();
        void			    setSize();
        void			    createMenus();
        void			    createButtons();
        void				cleanButtonsArray();
        void				moveToCenter();
		void				startMoves();

    public slots:
        void				startNewGame();
        void				showOptionsWindow();
        void				showModesWindow();
        void			    buttonClicked();
};

#endif //!_MAINWINDOW_H_
