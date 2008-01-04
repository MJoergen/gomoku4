#ifndef _BUTTON_H_
# define _BUTTON_H_

# include <QPushButton>

# include "ButtonState.h"

class Button : public QPushButton
{
    Q_OBJECT

    private:
        int         id;
        int         size;
        buttonState state;

    private:
        void    changeIcon();

    public:
        Button(QWidget *parent, int size);

    public:
        int         GetId();
        buttonState GetState();
        void        SetState(buttonState state);

    public slots:
        void    changeState();
};

#endif //!_BUTTON_H_
