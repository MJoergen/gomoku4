#ifndef _BUTTON_H_
# define _BUTTON_H_

# include <QPushButton>

# include "Move.h"
# include "ButtonIconFactory.h"
# include "Player.h"

class Button : public QPushButton
{
    Q_OBJECT

    private:
        int				id;
        int				size;
        Move			*pos;
        PlayerNumber	state;

    private:
        void			changeIcon();

    public:
        Button(QWidget *parent, int size, int x, int y);
        ~Button();

    public:
        int				GetId();
        PlayerNumber	GetState();
        Move*			GetPos();
        void			SetState(PlayerNumber state);

    public slots:
        void			ChangeState();
};

#endif //!_BUTTON_H_
