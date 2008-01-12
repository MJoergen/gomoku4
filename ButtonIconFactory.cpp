#include "Images/red.xpm"
#include "Images/cyan.xpm"
#include "Images/white.xpm"
#include "Images/valid.xpm"
#include "Images/cancel.xpm"
#include "ButtonIconFactory.h"

ButtonIconFactory   *ButtonIconFactory::instance = NULL;

ButtonIconFactory::ButtonIconFactory()
{
    this->white.addPixmap(QPixmap(white_xpm));
    this->red.addPixmap(QPixmap(red_xpm));
    this->cyan.addPixmap(QPixmap(cyan_xpm));
    this->valid.addPixmap(QPixmap(valid_xpm));
    this->cancel.addPixmap(QPixmap(cancel_xpm));
}

ButtonIconFactory   *ButtonIconFactory::GetInstance()
{
    if (instance == NULL)
        instance = new ButtonIconFactory();
    return (instance);
}

QIcon   &ButtonIconFactory::GetIcon(TypeButton typeButton)
{
    switch (typeButton)
    {
        case RED    : return (this->red);
        case CYAN   : return (this->cyan);
        case WHITE  : return (this->white);
        case VALID  : return (this->valid);
        case CANCEL : return (this->cancel);
        default     : return (this->white);
    }
}

void    ButtonIconFactory::DestroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}
