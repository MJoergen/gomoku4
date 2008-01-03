#ifndef _MAINWINDOW_H_
# define _MAINWINDOW_H_

# include <QMenu>
# include <QAction>
# include <QMainWindow>

# include "Button.h"
# include "AlgorithmType.h"
# include "OptionsWindow.h"

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
        QAction             *quitAction;
        QAction             *optionsAction;
        Button              **buttonsArray;
        OptionsWindow       *optionsWindow;

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
        void    showOptionsWindow();
};

#endif //!_MAINWINDOW_H_
