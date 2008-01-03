#ifndef _BUTTON_H_
# define _BUTTON_H_

# include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT

    private:
        typedef enum
        {
            NEUTRAL,
            PLAYER1,
            PLAYER2
        }   buttonState;

    private:
        int         id;
        int         size;
        buttonState state;

    private:
        void    changeIcon();

    public:
        Button(QWidget *parent, int size);

    public:
        int     GetId();

    private slots:
        void    changeState();
};

#endif //!_BUTTON_H_
