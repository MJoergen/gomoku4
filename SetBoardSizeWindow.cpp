#include "Images/valid.xpm"
#include "Images/cancel.xpm"
#include "SetBoardSizeWindow.h"

SetBoardSizeWindow::SetBoardSizeWindow(Mainwindow *mainwindow) : mainwindow(mainwindow)
{
    this->resize(WIDTH, HEIGHT);
    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);
    this->hboxLayout = new QHBoxLayout(this);

    this->spinBox_boardSize = new QSpinBox(this);
    this->spinBox_boardSize->setMinimum(MIN);
    this->hboxLayout->addWidget(this->spinBox_boardSize);

    this->button_valid = new QPushButton("Valid", this);
    this->button_valid->setIcon(QIcon(QPixmap(valid_xpm)));
    this->hboxLayout->addWidget(this->button_valid);

    this->button_cancel = new QPushButton("Cancel", this);
    this->button_cancel->setIcon(QIcon(QPixmap(cancel_xpm)));
    this->hboxLayout->addWidget(this->button_cancel);

    this->doConnects();
    this->show();
}

void    SetBoardSizeWindow::doConnects()
{
    connect(this->button_valid, SIGNAL(clicked()), this, SLOT(valid()));
    connect(this->button_cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void    SetBoardSizeWindow::valid()
{
    this->mainwindow->SetBoardSize(this->spinBox_boardSize->value());
    this->mainwindow->CreateBoard();
    this->close();
}

SetBoardSizeWindow::~SetBoardSizeWindow()
{
    delete this->hboxLayout;
    delete this->spinBox_boardSize;
    delete this->button_valid;
    delete this->button_cancel;
}
