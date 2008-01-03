#include "Button.h"
#include "Images/red.xpm"
#include "Images/cyan.xpm"
#include "Images/white.xpm"

Button::Button(QWidget *parent, int size) : size(size)
{
    this->setFlat(true);
    this->state = NEUTRAL;
    this->setParent(parent);
    this->changeIcon();
    connect(this, SIGNAL(clicked()), SLOT(changeState()));
    this->show();
}

void    Button::changeIcon()
{
    switch (this->state)
    {
        case NEUTRAL:
            this->setIconSize(QSize(this->size, this->size));
            this->setIcon(QIcon(QPixmap(white_xpm)));
            break;
        case PLAYER1:
            this->setIconSize(QSize(this->size, this->size));
            this->setIcon(QIcon(QPixmap(red_xpm)));
            break;
        case PLAYER2:
            this->setIconSize(QSize(this->size, this->size));
            this->setIcon(QIcon(QPixmap(cyan_xpm)));
            break;
    }
}

void    Button::changeState()
{
    if (this->state == NEUTRAL || this->state == PLAYER2)
    {
        this->setIcon(QIcon(QPixmap(red_xpm)));
        this->state = PLAYER1;
    }
    else
    {
        this->setIcon(QIcon(QPixmap(cyan_xpm)));
        this->state = PLAYER2;
    }
}

int Button::GetId()
{
    return (this->id);
}
