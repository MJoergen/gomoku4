#include "Images/valid.xpm"
#include "Images/cancel.xpm"
#include "ButtonIconFactory.h"

ButtonIconFactory   *ButtonIconFactory::instance = NULL;

ButtonIconFactory::ButtonIconFactory()
{
    this->grid.addPixmap(QPixmap("Images/Grid.png"));
    this->black.addPixmap(QPixmap("Images/Black.png"));
    this->white.addPixmap(QPixmap("Images/White.png"));
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
        case WHITE      : return (this->white);
        case BLACK      : return (this->black);
        case GRID       : return (this->grid);
        case VALID      : return (this->valid);
        case CANCEL     : return (this->cancel);
        default         : return (this->white);
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
