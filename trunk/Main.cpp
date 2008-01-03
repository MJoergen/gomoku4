#include <QApplication>

#include "Mainwindow.h"

int              main(int ac, char **av)
{
    QApplication app(ac, av);
    Mainwindow   mainwindow;

    return (app.exec());
}
