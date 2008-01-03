#include <QMenuBar>
#include <iostream>
#include "Mainwindow.h"

Mainwindow::Mainwindow()
{
    this->init();
    this->createMenus();
    this->CreateBoard();
    this->doConnects();
    this->show();
}

void    Mainwindow::init()
{
    this->boardSize = DEFAULT_BOARDSIZE;
    this->buttonsArray = NULL;
}

void    Mainwindow::setSize()
{
    int width  = this->boardSize * DEFAULT_BUTTONSIZE;
    int height = this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT * 2;

    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
}

void    Mainwindow::createMenus()
{
    this->fileMenu = this->menuBar()->addMenu("&File");
    this->quitAction = new QAction(tr("&Quit"), this);
    this->quitAction->setShortcut(tr("Ctrl+Q"));
    this->quitAction->setStatusTip(tr("Quit application"));
    this->fileMenu->addAction(this->quitAction);

    this->preferenceMenu = this->menuBar()->addMenu("&Preference");
    this->setBoardSizeAction = new QAction(tr("&Board size"), this);
    this->setBoardSizeAction->setShortcut(tr("Ctrl+S"));
    this->setBoardSizeAction->setStatusTip(tr("Set board size"));
    this->preferenceMenu->addAction(this->setBoardSizeAction);
}

void    Mainwindow::doConnects()
{
    connect(this->quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->setBoardSizeAction, SIGNAL(triggered()), this, SLOT(showSetBoardSizeWindow()));
}

void    Mainwindow::showSetBoardSizeWindow()
{
    this->setBoardSizeWindow = new SetBoardSizeWindow(this);
}

void    Mainwindow::cleanButtonsArray()
{
    if (this->buttonsArray)
    {
        int nbButtons = this->boardSize * this->boardSize;
        for (int i = 0; i < nbButtons; i++)
            delete this->buttonsArray[i];
        delete [] this->buttonsArray;
        this->buttonsArray = NULL;
    }
}

void    Mainwindow::createButtons()
{
    int nbButtons = this->boardSize * this->boardSize;
    this->buttonsArray = new Button*[nbButtons];
    for (int i = 0, x = 0, y = 0; i < nbButtons; i++, x++)
    {
        if (x == this->boardSize)
        {
            x = 0;
            y++;
        }
        this->buttonsArray[i] = new Button(this, DEFAULT_BUTTONSIZE);
        this->buttonsArray[i]->resize(DEFAULT_BUTTONSIZE, DEFAULT_BUTTONSIZE);
        this->buttonsArray[i]->move(x * DEFAULT_BUTTONSIZE, y * DEFAULT_BUTTONSIZE + MENU_HEIGHT);
        this->buttonsArray[i]->show();
    }
}

void    Mainwindow::SetBoardSize(int boardSize)
{
    this->cleanButtonsArray();
    this->boardSize = boardSize;
}

void    Mainwindow::CreateBoard()
{
    this->setSize();
    this->createButtons();
}
