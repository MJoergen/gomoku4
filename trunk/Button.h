#ifndef _BUTTON_H_
# define _BUTTON_H_

# include <QPushButton>

# include "Move.h"
# include "ButtonState.h"
# include "ButtonIconFactory.h"

class Button : public QPushButton
{
    Q_OBJECT

    private:
        int         id;
        int         size;
        Move        *pos;
        buttonState state;

    private:
        void    changeIcon();

    public:
        Button(QWidget *parent, int size, int x, int y);
        ~Button();

    public:
        int         GetId();
        buttonState GetState();
        Move*       GetPos();
        void        SetState(buttonState state);

    public slots:
        void    ChangeState();
};

#endif //!_BUTTON_H_
