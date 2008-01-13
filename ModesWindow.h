#ifndef _MODESWINDOW_H_
# define _MODESWINDOW_H_

# define WIDTH  195
# define HEIGHT 180

# include <QGroupBox>
# include <QVBoxLayout>
# include <QGridLayout>
# include <QPushButton>
# include <QRadioButton>

# include "ModeType.h"
# include "Mainwindow.h"

class ModesWindow : public QWidget
{
    Q_OBJECT

    private:
        QGroupBox       *groupBox;
        QVBoxLayout     *modesLayout;
        QGridLayout     *generalLayout;
        QRadioButton    *rb_playerVsPlayer;
        QRadioButton    *rb_playerVsIa;
        QRadioButton    *rb_IaVsIa;
        QPushButton     *b_valid;
        QPushButton     *b_cancel;

    public:
        ModesWindow(Mode mode);
        ~ModesWindow();

    public:
        void    moveToCenter();

    public slots:
        void    valid();
        void    cancel();
};

#endif //!_MODESWINDOW_H_
