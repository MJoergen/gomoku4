#include "Images/pion1.xpm"
#include "Images/pion2.xpm"
#include "Images/freeCase.xpm"
#include "Images/valid.xpm"
#include "Images/cancel.xpm"
#include "ButtonIconFactory.h"

ButtonIconFactory   *ButtonIconFactory::instance = NULL;

ButtonIconFactory::ButtonIconFactory()
{
    this->freeCase.addPixmap(QPixmap(freeCase_xpm));
    this->pion1.addPixmap(QPixmap(pion1_xpm));
    this->pion2.addPixmap(QPixmap(pion2_xpm));
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
        case PION1      : return (this->pion1);
        case PION2      : return (this->pion2);
        case FREECASE   : return (this->freeCase);
        case VALID      : return (this->valid);
        case CANCEL     : return (this->cancel);
        default         : return (this->freeCase);
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
