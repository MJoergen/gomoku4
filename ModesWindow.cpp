#include "ModesWindow.h"
#include "ButtonIconFactory.h"

ModesWindow::ModesWindow(Mode mode)
{
    this->setWindowTitle("Modes");
    this->resize(WIDTH, HEIGHT);
    this->setMinimumSize(WIDTH, HEIGHT);
    this->setMaximumSize(WIDTH, HEIGHT);
    this->groupBox = new QGroupBox("Choose a game mode", this);
    this->generalLayout = new QGridLayout(this);
    this->modesLayout = new QVBoxLayout(this->groupBox);

    this->rb_playerVsPlayer = new QRadioButton("Player VS Player", this->groupBox);
    if (mode == PLAYER_VS_PLAYER)
        this->rb_playerVsPlayer->setChecked(true);
    this->rb_playerVsIa = new QRadioButton("Player VS IA", this->groupBox);
    if (mode == PLAYER_VS_IA)
        this->rb_playerVsIa->setChecked(true);
    this->rb_IaVsIa = new QRadioButton("IA VS IA", this->groupBox);
    if (mode == IA_VS_IA)
        this->rb_IaVsIa->setChecked(true);

    this->b_valid = new QPushButton("Valid", this);
    this->b_cancel = new QPushButton("Cancel", this);
    this->b_valid->setIcon(ButtonIconFactory::GetInstance()->GetIcon(VALID));
    this->b_cancel->setIcon(ButtonIconFactory::GetInstance()->GetIcon(CANCEL));
    connect(this->b_valid, SIGNAL(clicked()), this, SLOT(valid()));
    connect(this->b_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    this->modesLayout->addWidget(this->rb_playerVsPlayer);
    this->modesLayout->addWidget(this->rb_playerVsIa);
    this->modesLayout->addWidget(this->rb_IaVsIa);
    this->generalLayout->addWidget(this->groupBox, 0, 0, 1, 2);
    this->generalLayout->addWidget(this->b_valid, 1, 0, 1, 1);
    this->generalLayout->addWidget(this->b_cancel, 1, 1, 1, 1);
    this->moveToCenter();
    this->show();
}

void    ModesWindow::moveToCenter()
{
    this->move(Mainwindow::GetInstance()->x() + Mainwindow::GetInstance()->width() / 2 - this->width() / 2,
               Mainwindow::GetInstance()->y() + Mainwindow::GetInstance()->height() / 2 - this->height() / 2);
}

void    ModesWindow::valid()
{
    if (this->rb_playerVsPlayer->isChecked())
        Mainwindow::GetInstance()->SetMode(PLAYER_VS_PLAYER);
    else if (this->rb_playerVsIa->isChecked())
        Mainwindow::GetInstance()->SetMode(PLAYER_VS_IA);
    else
        Mainwindow::GetInstance()->SetMode(IA_VS_IA);
    delete this;
}

void    ModesWindow::cancel()
{
    delete this;
}

ModesWindow::~ModesWindow()
{
    delete this->rb_playerVsPlayer;
    delete this->rb_playerVsIa;
    delete this->rb_IaVsIa;
    delete this->modesLayout;
    delete this->groupBox;
    delete this->b_valid;
    delete this->b_cancel;
    delete this->generalLayout;
}
