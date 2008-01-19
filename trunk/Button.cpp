#include "Button.h"


Button::Button(QWidget *parent, int size, int x, int y) : size(size)
{
    this->pos = new Move(x, y);
    this->setFlat(true);
    this->state = NEUTRAL;
    this->setParent(parent);
    this->changeIcon();
    this->show();
}

void    Button::changeIcon()
{
    switch (this->state)
    {
        case NEUTRAL:
            this->setIconSize(QSize(this->size, this->size));
            this->setIcon(ButtonIconFactory::GetInstance()->GetIcon(GRID));
            break;
        case PLAYER1:
            this->setIconSize(QSize(this->size, this->size));
            this->setIcon(ButtonIconFactory::GetInstance()->GetIcon(WHITE));
            break;
        case PLAYER2:
            this->setIconSize(QSize(this->size, this->size));
            this->setIcon(ButtonIconFactory::GetInstance()->GetIcon(BLACK));
            break;
    }
}

void    Button::ChangeState()
{
	this->changeIcon();
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
