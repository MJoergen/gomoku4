#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTimer>

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
    this->statistics = new Statistics(this);
    this->frame = new QFrame(this);
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
    int width  = this->boardSize * DEFAULT_BUTTONSIZE + STATS_PANEL_WIDTH +
                 STATS_PANEL_SPACE * 2 + BORDURE_SIZE - 1;
    int height = this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT + BORDURE_SIZE;

    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    this->frame->setGeometry(0, 0,
                            this->boardSize * DEFAULT_BUTTONSIZE + BORDURE_SIZE + 1,
                            this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT + BORDURE_SIZE);
    this->frame->setFrameShape(QFrame::WinPanel);
    this->frame->setFrameShadow(QFrame::Raised);
    this->frame->setLineWidth(1);
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
            this->buttonsArray[x][y] = new Button(this->frame, DEFAULT_BUTTONSIZE, x, y);
            this->buttonsArray[x][y]->resize(DEFAULT_BUTTONSIZE, DEFAULT_BUTTONSIZE);
            this->buttonsArray[x][y]->move(x * DEFAULT_BUTTONSIZE + 1, y * DEFAULT_BUTTONSIZE + MENU_HEIGHT + 1);
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

void			Mainwindow::StartMoves()
{
	while ((this->moveActionState = Gomoku::GetInstance()->DoNextMove()) == DONE)
	{
		QTimer::singleShot(500, this, SLOT(updateDisplay()));
	}
	if (this->checkGameState() != IN_PROGRESS)
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
		{
			this->buttonsArray[(*it).GetX()][(*it).GetY()]->SetState(NEUTRAL);
			std::cout << "Point pris X:" << (*it).GetX() << " Y:" << (*it).GetY() << std::endl;
		}
        this->statistics->UpdateStatistics();
	}
}

GameState		Mainwindow::checkGameState()
{
	GameState gameState = Gomoku::GetInstance()->GetGameState();
    switch (gameState)
    {
        case VICTORY_PLAYER1 :
            QMessageBox::information(this, "Gomoku - Game information",
                                     "Player 1 wins !");
			break;

        case VICTORY_PLAYER2 :
            QMessageBox::information(this, "Gomoku - Game information",
                                     "Player 2 wins !");
			break;

        case BOARD_FULL :
            QMessageBox::information(this, "Gomoku - Game information",
                                     "The board is full.\nA new game is being to start.");
			break;

		default :
			break;
    }
	return (gameState);
}

// Public QT slots

void			Mainwindow::startNewGame()
{
    this->cleanButtonsArray();
    this->createButtons();
    Gomoku::GetInstance()->ResetGame();
    this->statistics->Reset();
	this->StartMoves();
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
		if (this->moveActionState == WAITING_PLAYER_ACTION)
		{
			MoveState moveState = Gomoku::GetInstance()->CommitMove(button->GetPos(), true);
			switch (moveState)
			{
				case GOOD_MOVE :
					this->updateDisplay();
					if (this->checkGameState() != IN_PROGRESS)
						this->startNewGame();
					else
						this->StartMoves();
					break;

				case NOT_FREE :
					QMessageBox::critical(this, "Gomoku - Illegal action",
                                          "This pion is not free. You are not allowed to use it.");
					break;

				case DOUBLE_THREE:
					QMessageBox::critical(this, "Gomoku - Illegal action",
                                          "Double three !");
					break;
			}
		}
    }
}
