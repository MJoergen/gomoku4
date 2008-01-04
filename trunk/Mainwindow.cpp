#include <QMenuBar>
#include <QDesktopWidget>
#include <iostream>
#include "Mainwindow.h"

Mainwindow *Mainwindow::instance = NULL;

Mainwindow::Mainwindow()
{
    this->init();
    this->createMenus();
    this->CreateBoard();
    this->createIa();
    this->doConnects();
    this->show();
}

Mainwindow    *Mainwindow::GetInstance()
{
    if (instance == NULL)
        instance = new Mainwindow();
    return (instance);
}

void    Mainwindow::init()
{
    this->ia = NULL;
    this->boardSize = DEFAULT_BOARDSIZE;
    this->algo = ALPHABETA;
    this->buttonsArray = NULL;
    this->moveToCenter();
    Gomoku::GetInstance()->SetSize(DEFAULT_BOARDSIZE);
    Gomoku::GetInstance()->SetAlgorithm(ALPHABETA);
}

void    Mainwindow::moveToCenter()
{
    QDesktopWidget desktop;
    this->move(desktop.screenGeometry().width() / 2 - this->width() / 2,
               desktop.screenGeometry().height() / 2 - this->height() / 2);
}

void    Mainwindow::createIa()
{
    if (this->ia)
        delete ia;
    switch(this->algo)
    {
        case ALPHABETA:
            this->ia = new AlphaBeta();
            break;

        case NEGAMAX:
            this->ia = new NegaMax();
            break;
    }
}

void    Mainwindow::setSize()
{
    int width  = this->boardSize * DEFAULT_BUTTONSIZE;
    int height = this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT * 2;

    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    Gomoku::GetInstance()->SetSize(this->boardSize);
}

void    Mainwindow::SetAlgorithm(AlgorithmType algo)
{
    this->algo = algo;
    this->createIa();
    Gomoku::GetInstance()->SetAlgorithm(this->algo);
}

void    Mainwindow::createMenus()
{
    this->fileMenu = this->menuBar()->addMenu("&File");

    this->newGameAction = new QAction(tr("&New game"), this);
    this->newGameAction->setShortcut(tr("Ctrl+N"));
    this->newGameAction->setStatusTip(tr("Start a new game"));
    this->fileMenu->addAction(this->newGameAction);

    this->quitAction = new QAction(tr("&Quit"), this);
    this->quitAction->setShortcut(tr("Ctrl+Q"));
    this->quitAction->setStatusTip(tr("Quit application"));
    this->fileMenu->addAction(this->quitAction);

    this->preferenceMenu = this->menuBar()->addMenu("&Preference");

    this->optionsAction = new QAction(tr("&Options"), this);
    this->optionsAction->setShortcut(tr("Ctrl+O"));
    this->optionsAction->setStatusTip(tr("Set game options"));
    this->preferenceMenu->addAction(this->optionsAction);
}

void    Mainwindow::doConnects()
{
    connect(this->newGameAction, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(this->quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsWindow()));
}

void    Mainwindow::startNewGame()
{
    this->cleanButtonsArray();
    this->createButtons();
}

void    Mainwindow::showOptionsWindow()
{
    this->optionsWindow = new OptionsWindow();
}

void    Mainwindow::buttonClicked()
{
    Button *button = dynamic_cast<Button *>(sender());

    if (button)
        Gomoku::GetInstance()->commitMove(button->GetPos(), false);
    this->IaPlay();
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

void             Mainwindow::createButtons()
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
        this->buttonsArray[i] = new Button(this, DEFAULT_BUTTONSIZE, x, y);
        this->buttonsArray[i]->resize(DEFAULT_BUTTONSIZE, DEFAULT_BUTTONSIZE);
        this->buttonsArray[i]->move(x * DEFAULT_BUTTONSIZE, y * DEFAULT_BUTTONSIZE + MENU_HEIGHT);
        this->buttonsArray[i]->show();
        Gomoku::GetInstance()->SetBoard(this->buttonsArray);
        connect(this->buttonsArray[i], SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }
}

void    Mainwindow::SetBoardSize(int boardSize)
{
    this->cleanButtonsArray();
    this->boardSize = boardSize;
}

void    Mainwindow::IaPlay()
{
    if (this->ia)
        this->ia->findMove();
}

void    Mainwindow::CreateBoard()
{
    this->setSize();
    this->createButtons();
}

void    Mainwindow::DestroyInstance()
{
    if (instance)
        delete instance;
}

Mainwindow::~Mainwindow()
{
}
