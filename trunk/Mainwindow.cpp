#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QDesktopWidget>

#include "Mainwindow.h"

Mainwindow *Mainwindow::instance = NULL;

// Constructor

Mainwindow::Mainwindow()
{
    this->init();
    this->createMenus();
    this->CreateBoard();
    this->doConnects();
	this->show();
}

// Destructor

Mainwindow::~Mainwindow()
{
    delete this->statistics;
    delete this->referee;
    ButtonIconFactory::DestroyInstance();
    Gomoku::DestroyInstance();
}

// Singleton methods

Mainwindow		*Mainwindow::GetInstance()
{
    if (instance == NULL)
        instance = new Mainwindow();
    return (instance);
}

void			Mainwindow::DestroyInstance()
{
    if (instance)
    {
        instance = NULL;
        delete instance;
    }
}

// Public methods

void			Mainwindow::CreateBoard()
{
    this->setSize();
    this->moveToCenter();
    this->startNewGame();
}

void			Mainwindow::SetBoardSize(int boardSize)
{
    this->cleanButtonsArray();
    this->boardSize = boardSize;
}

Statistics      *Mainwindow::GetStatistics()
{
    return (this->statistics);
}

// Private methods

void			Mainwindow::init()
{
    this->buttonsArray = NULL;
    this->statistics = NULL;
    this->boardSize = DEFAULT_BOARDSIZE;
    this->referee = new Referee(this);
    this->statistics = new Statistics(this);
    Gomoku::GetInstance()->SetSize(DEFAULT_BOARDSIZE);
}

void			Mainwindow::doConnects()
{
    connect(this->newGameAction, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(this->quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsWindow()));
}

void			Mainwindow::setSize()
{
    int width  = this->boardSize * DEFAULT_BUTTONSIZE + STATS_PANEL_WIDTH + 10;
    int height = this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT;

    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    if (this->statistics)
        this->statistics->UpdateSize(this->boardSize);
    Gomoku::GetInstance()->SetSize(this->boardSize);
}

void			Mainwindow::createMenus()
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

    this->preferenceMenu = this->menuBar()->addMenu("&Preferences");

    this->optionsAction = new QAction(tr("&Options"), this);
    this->optionsAction->setShortcut(tr("Ctrl+O"));
    this->optionsAction->setStatusTip(tr("Set game options"));
    this->preferenceMenu->addAction(this->optionsAction);
}

void			Mainwindow::createButtons()
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
}

void			Mainwindow::cleanButtonsArray()
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

void			Mainwindow::moveToCenter()
{
    QDesktopWidget desktop;
    this->move(desktop.screenGeometry().width() / 2 - this->width() / 2,
               desktop.screenGeometry().height() / 2 - this->height() / 2);
}

void			Mainwindow::startMoves()
{
	while ((this->moveState = Gomoku::GetInstance()->DoNextMove()) == DONE)
	{
		this->updateDisplay();
	}
	if (this->referee->CheckGame() != IN_PROGRESS)
		this->startNewGame();
}

void			Mainwindow::updateDisplay()
{
	Move* move = Gomoku::GetInstance()->GetLastMove();
	if (move != NULL)
	{
		this->buttonsArray[move->GetX()][move->GetY()]->SetState(Gomoku::GetInstance()->GetPlayerToMove());
		std::list<Point>::iterator it;
		std::list<Point> pointsTaken = move->GetPointsTaken();

		for (it = pointsTaken.begin(); it != pointsTaken.end(); it++)
			this->buttonsArray[(*it).GetX()][(*it).GetY()]->SetState(NEUTRAL);
	}
}

// Public QT slots

void			Mainwindow::startNewGame()
{
    this->cleanButtonsArray();
    this->createButtons();
    Gomoku::GetInstance()->ResetGame();
	this->startMoves();
}

void			Mainwindow::showOptionsWindow()
{
    new OptionsWindow(this->boardSize);
}

void			Mainwindow::buttonClicked()
{
    Button *button = dynamic_cast<Button *>(sender());

    if (button)
    {
		if (this->moveState == WAITING_PLAYER_ACTION)
		{
			if (this->referee->CheckMove(this->buttonsArray, button->GetPos()) == ALLOWED)
			{
				Gomoku::GetInstance()->CommitMove(button->GetPos(), true);
				this->updateDisplay();
                if (this->referee->CheckGame() != IN_PROGRESS)
                    this->startNewGame();
				else
					this->startMoves();
			}
		}
    }
}
