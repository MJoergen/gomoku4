#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QMainWindow>

# include "Button.h"
# include "AlgorithmType.h"
# include "SetBoardSizeWindow.h"

# define DEFAULT_BOARDSIZE  5
# define DEFAULT_BUTTONSIZE 50
# define MENU_HEIGHT        25

class SetBoardSizeWindow;

class Mainwindow : public QMainWindow
{
    Q_OBJECT

    private:
        int                 boardSize;
        AlgorithmType       algo;
        QMenu               *fileMenu;
        QMenu               *preferenceMenu;
        QAction             *quitAction;
        QAction             *setBoardSizeAction;
        Button              **buttonsArray;
        SetBoardSizeWindow  *setBoardSizeWindow;

    public:
        Mainwindow();

    public:
        void    CreateBoard();
        void    SetBoardSize(int boardSize);
        void    SetAlgorithm(AlgorithmType algo);

    private:
        void    init();
        void    doConnects();
        void    setSize();
        void    createMenus();
        void    createButtons();
        void    cleanButtonsArray();

    public slots:
        void    showSetBoardSizeWindow();
};

#endif //!_MAINWINDOW_H_
