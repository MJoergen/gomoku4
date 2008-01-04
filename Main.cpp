#include <QApplication>

#include "Mainwindow.h"

int              main(int ac, char **av)
{
    int          res;

    QApplication app(ac, av);
    Mainwindow   *mainwindow = Mainwindow::GetInstance();

    res = app.exec();
    if (mainwindow)
        Mainwindow::DestroyInstance();

    return (res);
}
