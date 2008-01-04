#include <QMenuBar>
#include <QStatusBar>
#include <QDesktopWidget>

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
    this->ia              = NULL;
    this->buttonsArray    = NULL;
    this->statisticsPanel = NULL;
    this->algo            = ALPHABETA;
    this->boardSize       = DEFAULT_BOARDSIZE;
    this->statisticsPanel = new StatisticsPanel(this);
    Gomoku::GetInstance()->SetSize(DEFAULT_BOARDSIZE);
    Gomoku::GetInstance()->SetAlgorithm(ALPHABETA);
    this->UpdateStatistics(0);
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
    int width  = this->boardSize * DEFAULT_BUTTONSIZE + STATS_PANEL_WIDTH + 5;
    int height = this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT;

    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    if (this->statisticsPanel)
        this->statisticsPanel->UpdateSize(this->boardSize);
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
    this->optionsWindow = new OptionsWindow(this->boardSize);
}

void    Mainwindow::buttonClicked()
{
    Button *button = dynamic_cast<Button *>(sender());

    if (button)
        Gomoku::GetInstance()->commitMove(button->GetPos(), true);
    this->IaPlay();
}

void    Mainwindow::cleanButtonsArray()
{
    if (this->buttonsArray)
    {
        for (int x = 0; x < this->boardSize; x++)
        {
            for (int y = 0; y < this->boardSize; y++)
                delete this->buttonsArray[x][y];
        }
        delete [] this->buttonsArray;
        this->buttonsArray = NULL;
    }
}

void    Mainwindow::createButtons()
{
    this->buttonsArray = new Button**[this->boardSize];
    for(int i = 0; i < this->boardSize; i++)
        this->buttonsArray[i] = new Button*[this->boardSize];

    for (int x = 0; x < this->boardSize; x++)
    {
        for (int y = 0; y < this->boardSize; y++)
        {
            this->buttonsArray[x][y] = new Button(this, DEFAULT_BUTTONSIZE, x, y);
            this->buttonsArray[x][y]->resize(DEFAULT_BUTTONSIZE, DEFAULT_BUTTONSIZE);
            this->buttonsArray[x][y]->move(x * DEFAULT_BUTTONSIZE, y * DEFAULT_BUTTONSIZE + MENU_HEIGHT);
            this->buttonsArray[x][y]->show();
            connect(this->buttonsArray[x][y], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
    Gomoku::GetInstance()->SetBoard(this->buttonsArray);
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
    this->moveToCenter();
}

void    Mainwindow::UpdateStatistics(int nbConsideredNode)
{
    //if (this->algo == ALPHABETA)
       // this->infos->setText(QString("Algorithm : AlphaBeta - Nodes : %1").arg(nbConsideredNode));
    //else
        //this->infos->setText(QString("Algorithm : NegaMax - Nodes :  %1").arg(nbConsideredNode));
}

void    Mainwindow::DestroyInstance()
{
    if (instance)
        delete instance;
}

Mainwindow::~Mainwindow()
{
}
