#ifndef _BUTTONICONFACTORY_H_
# define _BUTTONICONFACTORY_H_

# include <QIcon>

typedef enum
{
    WHITE,
    RED,
    CYAN
}   TypeButton;

class ButtonIconFactory
{
    private:
        QIcon   white;
        QIcon   red;
        QIcon   cyan;

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
