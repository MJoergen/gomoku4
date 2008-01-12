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

ModesWindow::~ModesWindow()
{
    delete this->groupBox;
}
