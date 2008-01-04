#include "Button.h"
#include "Images/red.xpm"
#include "Images/cyan.xpm"
#include "Images/white.xpm"

Button::Button(QWidget *parent, int size, int x, int y) : size(size)
{
    this->pos = new Move(x, y);
    this->setFlat(true);
    this->state = NEUTRAL;
    this->setParent(parent);
    this->changeIcon();
    //connect(this, SIGNAL(clicked()), SLOT(ChangeState()));
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

void    Button::ChangeState()
{
    if (this->state == NEUTRAL || this->state == PLAYER1)
        this->setIcon(QIcon(QPixmap(red_xpm)));
    else
        this->setIcon(QIcon(QPixmap(cyan_xpm)));
}

int Button::GetId()
{
    return (this->id);
}

buttonState Button::GetState()
{
    return (this->state);
}

Move    *Button::GetPos()
{
    return (this->pos);
}

void    Button::SetState(buttonState state)
{
    this->state = state;
}

Button::~Button()
{
    delete this->pos;
}
