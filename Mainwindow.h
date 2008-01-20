#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QLabel>
# include <QMainWindow>

# include "Button.h"
# include "Gomoku.h"
# include "OptionsWindow.h"
# include "Statistics.h"
# include "ButtonIconFactory.h"

# define DEFAULT_BOARDSIZE  19
# define DEFAULT_BUTTONSIZE 30
# define MENU_HEIGHT        25
# define STATS_PANEL_WIDTH  190

class OptionsWindow;
class Alphabeta;
class NegaMax;
class Statistics;
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

    private:
        int                 boardSize;
        Button				***buttonsArray;
        Statistics          *statistics;
		MoveActionState		moveActionState;

    private:
        Mainwindow();
        ~Mainwindow();

	public:
        static Mainwindow  *GetInstance();
        static void        DestroyInstance();

    public:
        void               CreateBoard();
        void               SetBoardSize(int boardSize);
        Statistics         *GetStatistics();

    private:
        void				init();
        void				doConnects();
        void			    setSize();
        void			    createMenus();
        void			    createButtons();
        void				cleanButtonsArray();
        void				moveToCenter();
		void				startMoves();
		void				updateDisplay();
		GameState			checkGameState();

    public slots:
        void				startNewGame();
        void				showOptionsWindow();
        void			    buttonClicked();
};

#endif //!_MAINWINDOW_H_
