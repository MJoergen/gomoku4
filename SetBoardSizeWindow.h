#ifndef _OPTIONSWINDOW_H_
# define _OPTIONSWINDOW_H_

# include <QSpinBox>
# include <QHBoxLayout>
# include <QPushButton>
# include <QMainWindow>
# include <QRadioButton>
# include <QGroupBox>
# include <QLabel>

# include "AlgorithmType.h"
# include "Mainwindow.h"

# define MIN    5
# define MIN    5
# define WIDTH  195
# define HEIGHT 180

class Mainwindow;

class OptionsWindow : public QWidget
{
    Q_OBJECT

    private:
        QHBoxLayout  *hboxLayout;
        QSpinBox     *spinBox_boardSize;
        QPushButton  *button_valid;
        QPushButton  *button_cancel;
        QRadioButton *rb_alphaBeta;
        QRadioButton *rb_negaMax;
        QGroupBox    *groupBox;
        Mainwindow   *mainwindow;
        QLabel       *label;

    public:
       OptionsWindow(Mainwindow *mainwindow);
       ~OptionsWindow();

    private:
        void    doConnects();

    private slots:
        void    valid();
};

#endif //!_SETBOARDSIZEWINDOW_H_
