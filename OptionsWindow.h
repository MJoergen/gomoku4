#ifndef _OPTIONSWINDOW_H_
# define _OPTIONSWINDOW_H_

# include <QSpinBox>
# include <QHBoxLayout>
# include <QPushButton>
# include <QMainWindow>
# include <QRadioButton>
# include <QComboBox>
# include <QDesktopWidget>
# include <QGroupBox>
# include <QLabel>

# include "Mainwindow.h"
# include "Player.h"

# define MIN                  5
# define MAX                  19
# define OPTIONSWINDOW_WIDTH  280
# define OPTIONSWINDOW_HEIGHT 190

class Mainwindow;

class OptionsWindow : public QWidget
{
    Q_OBJECT

    private:
        QDesktopWidget  desktop;
        QSpinBox        *spinBox_boardSize;
        QPushButton     *button_valid;
        QPushButton     *button_cancel;
        QComboBox       *cb_player1;
        QComboBox       *cb_player1Algo;
        QComboBox       *cb_player2;
        QComboBox       *cb_player2Algo;
        QGroupBox       *groupBox;
        QGridLayout     *playerLayout;
        QGridLayout     *generalLayout;
        QPushButton     *b_valid;
        QPushButton     *b_cancel;
        QLabel          *l_player1;
        QLabel          *l_player2;
        QLabel          *l_boardSize;


    public:
       OptionsWindow(int boardSize);
       ~OptionsWindow();

    private:
        void    doConnects();
        void    moveToCenter();
        int     getMaxBoardSize();
        void    savePlayerType(PlayerNumber playerNum, QComboBox *player, QComboBox *algo);

    private slots:
        void    changingPlayer();
        void    valid();
        void    cancel();
};

#endif //!_SETBOARDSIZEWINDOW_H_
