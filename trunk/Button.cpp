#include "Button.h"

Button::Button(QWidget *parent, int size, int x, int y) : size(size)
{
    this->pos = new Move(x, y, NEUTRAL);
    this->setFlat(true);
    this->setParent(parent);
    this->changeIcon();
    this->show();
}

Button::~Button()
{
    delete this->pos;
}

void			Button::changeIcon()
{
    switch (this->pos->GetPlayerNumber())
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

int				Button::GetId()
{
    return (this->id);
}

PlayerNumber	Button::GetState()
{
    return (this->pos->GetPlayerNumber());
}

Move			*Button::GetPos()
{
    return (this->pos);
}

void			Button::SetState(PlayerNumber state)
{
    this->pos->SetPlayerNumber(state);
	this->changeIcon();
}
