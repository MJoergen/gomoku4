#include <QDesktopWidget>

#include "Images/valid.xpm"
#include "Images/cancel.xpm"
#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(int boardSize)
{
    this->setWindowTitle("Options");
    this->resize(WIDTH, HEIGHT);
    this->moveToCenter();
    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);

    this->groupBox = new QGroupBox("Algorithms", this);
    this->groupBox->setGeometry(QRect(10, 10, 171, 80));

    this->rb_alphaBeta = new QRadioButton("Alpha Beta", this->groupBox);
    this->rb_alphaBeta->setChecked(true);
    this->rb_alphaBeta->setGeometry(QRect(10, 20, 99, 23));

    this->rb_negaMax = new QRadioButton("Nega Max", this->groupBox);
    this->rb_negaMax->setGeometry(QRect(10, 50, 99, 23));

    this->spinBox_boardSize = new QSpinBox(this);
    this->spinBox_boardSize->setMinimum(MIN);
    this->spinBox_boardSize->setValue(boardSize);
    this->spinBox_boardSize->setGeometry(QRect(100, 96, 80, 27));

    this->label = new QLabel("Board size", this);
    this->label->setGeometry(QRect(10, 100, 70, 18));

    this->button_valid = new QPushButton("Valid", this);
    this->button_valid->setIcon(QIcon(QPixmap(valid_xpm)));
    this->button_valid->setGeometry(QRect(10, 130, 80, 30));

    this->button_cancel = new QPushButton("Cancel", this);
    this->button_cancel->setIcon(QIcon(QPixmap(cancel_xpm)));
    this->button_cancel->setGeometry(QRect(100, 130, 80, 30));

    this->doConnects();
    this->show();
}

void    OptionsWindow::moveToCenter()
{
    QDesktopWidget desktop;
    this->move(desktop.screenGeometry().width() / 2 - this->width() / 2,
               desktop.screenGeometry().height() / 2 - this->height() / 2);
}

void    OptionsWindow::doConnects()
{
    connect(this->button_valid, SIGNAL(clicked()), this, SLOT(valid()));
    connect(this->button_cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void    OptionsWindow::valid()
{
    Mainwindow::GetInstance()->SetBoardSize(this->spinBox_boardSize->value());
    Mainwindow::GetInstance()->SetAlgorithm(this->rb_alphaBeta->isChecked() ? ALPHABETA : NEGAMAX);
    Mainwindow::GetInstance()->CreateBoard();
    this->close();
}

OptionsWindow::~OptionsWindow()
{
    delete this->hboxLayout;
    delete this->spinBox_boardSize;
    delete this->button_valid;
    delete this->button_cancel;
}
