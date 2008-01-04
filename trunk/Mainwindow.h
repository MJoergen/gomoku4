#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QMainWindow>

# include "Button.h"
# include "gomoku.h"
# include "AlgorithmType.h"
# include "OptionsWindow.h"
# include "IA_alphabeta.h"
# include "IA_negamax.h"
# include "IA.h"

# define DEFAULT_BOARDSIZE  5
# define DEFAULT_BUTTONSIZE 50
# define MENU_HEIGHT        25

class OptionsWindow;

class Mainwindow : public QMainWindow
{
    Q_OBJECT

    private:
        int                 boardSize;
        AlgorithmType       algo;
        QMenu               *fileMenu;
        QMenu               *preferenceMenu;
        QAction             *newGameAction;
        QAction             *quitAction;
        QAction             *optionsAction;
        Button              **buttonsArray;
        OptionsWindow       *optionsWindow;
        IA                  *ia;
        static Mainwindow   *instance;

    private:
        Mainwindow();
        ~Mainwindow();

    public:
        void               IaPlay();
        void               CreateBoard();
        void               SetBoardSize(int boardSize);
        void               SetAlgorithm(AlgorithmType algo);
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
