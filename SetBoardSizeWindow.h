#ifndef _SETBOARDSIZEWINDOW_H_
# define _SETBOARDSIZEWINDOW_H_

# include <QSpinBox>
# include <QHBoxLayout>
# include <QPushButton>
# include <QMainWindow>

# include "Mainwindow.h"

# define MIN    5
# define WIDTH  250
# define HEIGHT 60

class Mainwindow;

class SetBoardSizeWindow : public QWidget
{
    Q_OBJECT

    private:
        QHBoxLayout *hboxLayout;
        QSpinBox    *spinBox_boardSize;
        QPushButton *button_valid;
        QPushButton *button_cancel;
        Mainwindow  *mainwindow;

    public:
       SetBoardSizeWindow(Mainwindow *mainwindow);
       ~SetBoardSizeWindow();

    private:
        void    doConnects();

    private slots:
        void    valid();
};

#endif //!_SETBOARDSIZEWINDOW_H_
