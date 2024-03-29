#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QLabel>
# include <QFrame>
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
# define STATS_PANEL_SPACE  5
# define BORDURE_SIZE       2

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
        QMenu               *gomokuMenu;
        QMenu               *preferenceMenu;
        QAction             *newGameAction;
        QAction             *quitAction;
        QAction             *pauseAction;
        QAction             *optionsAction;
        QFrame              *frame;
        QTimer              *timer;

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
        GameState			checkGameState();
        Statistics         *GetStatistics();

    private:
        void				init();
        void				doConnects();
        void			    setSize();
        void			    createMenus();
        void			    createButtons();
        void				cleanButtonsArray();
        void				moveToCenter();
        void				updateDisplay();

    public slots:
        void				startNewGame();
        void                pauseGame();
        void				showOptionsWindow();
        void			    buttonClicked();
        void			    StartMoves();
};

#endif //!_MAINWINDOW_H_
