#ifndef _BUTTONICONFACTORY_H_
# define _BUTTONICONFACTORY_H_

# include <QIcon>

typedef enum
{
    FREECASE,
    PION1,
    PION2,
    VALID,
    CANCEL
}   TypeButton;

class ButtonIconFactory
{
    private:
        QIcon   freeCase;
        QIcon   pion1;
        QIcon   pion2;
        QIcon   valid;
        QIcon   cancel;

    private:
        static  ButtonIconFactory   *instance;

    private:
        ButtonIconFactory();

    public:
        QIcon   &GetIcon(TypeButton typeButton);

    public:
        static ButtonIconFactory   *GetInstance();
        static void                 DestroyInstance();
};

#endif //!_BUTTONICONFACTORY_H_
