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
    delete this->statisticsPanel;
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

void			Mainwindow::SetAlgorithm(AlgorithmType algo)
{
    this->algo = algo;
    Gomoku::GetInstance()->SetAlgorithm(this->algo);
}

void            Mainwindow::SetMode(Mode mode)
{
    this->mode = mode;
    switch (mode)
    {
        case PLAYER_VS_PLAYER :
            Gomoku::GetInstance()->SetPlayer(1, IS_HUMAN);
            Gomoku::GetInstance()->SetPlayer(2, IS_HUMAN);
            break;

        case PLAYER_VS_IA :
            Gomoku::GetInstance()->SetPlayer(1, IS_HUMAN);
            Gomoku::GetInstance()->SetPlayer(2, IS_IA);
            break;

        case IA_VS_IA :
            Gomoku::GetInstance()->SetPlayer(1, IS_IA);
            Gomoku::GetInstance()->SetPlayer(2, IS_IA);
            this->startMoves();
            break;
    }
}

void			Mainwindow::UpdateStatistics(int nbConsideredNode)
{
    QString     player;
    QString     algorythm;
    QString     gameMode;

//    player      = this->isPlayer2Turn ? "IA" : "You";
    algorythm   = this->algo == ALPHABETA ? "AlphaBeta" : "NegaMax";
    switch (this->mode)
    {
        case PLAYER_VS_PLAYER :
            gameMode = "Player VS Player";
            break;

        case PLAYER_VS_IA :
            gameMode = "Player VS IA";
            break;

        case IA_VS_IA :
            gameMode = "IA VS IA";
            break;
    }
    this->statisticsPanel->UpdateStatistics(player, algorythm, gameMode,
                                            nbConsideredNode, 0,
                                            Gomoku::GetInstance()->GetNbMoves());
}

// Private methods

void			Mainwindow::init()
{
    this->buttonsArray = NULL;
    this->statisticsPanel = NULL;
    this->algo = ALPHABETA;
    this->boardSize = DEFAULT_BOARDSIZE;
    this->referee = new Referee(this);
    this->statisticsPanel = new StatisticsPanel(this);
	this->SetMode(PLAYER_VS_IA);
    Gomoku::GetInstance()->SetSize(DEFAULT_BOARDSIZE);
    Gomoku::GetInstance()->SetAlgorithm(ALPHABETA);
}

void			Mainwindow::doConnects()
{
    connect(this->newGameAction, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(this->quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsWindow()));
    connect(this->modesAction, SIGNAL(triggered()), this, SLOT(showModesWindow()));
}

void			Mainwindow::setSize()
{
    int width  = this->boardSize * DEFAULT_BUTTONSIZE + STATS_PANEL_WIDTH + 10;
    int height = this->boardSize * DEFAULT_BUTTONSIZE + MENU_HEIGHT;

    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    if (this->statisticsPanel)
        this->statisticsPanel->UpdateSize(this->boardSize);
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
    this->modesAction = new QAction(tr("&Modes"), this);
    this->modesAction->setShortcut(tr("Ctrl+M"));
    this->modesAction->setStatusTip(tr("Set game mode"));
    this->preferenceMenu->addAction(this->optionsAction);
    this->preferenceMenu->addAction(this->modesAction);
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
	this->board = new unsigned char**[this->boardSize];
	for (int x = 0; x < this->boardSize; x++)
		for (int y = 0; y < this->boardSize; y++)
			this->board[x][y] = (unsigned char *)NEUTRAL;
    Gomoku::GetInstance()->SetBoard(this->board);
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
	this->moveState = Gomoku::GetInstance()->DoNextMove();
	if (this->referee->CheckGame() != IN_PROGRESS)
		this->startNewGame();
}

// Public QT slots

void			Mainwindow::startNewGame()
{
    this->cleanButtonsArray();
    this->createButtons();
    Gomoku::GetInstance()->ResetGame();
    this->UpdateStatistics(0);
	this->startMoves();
}

void			Mainwindow::showOptionsWindow()
{
    new OptionsWindow(this->boardSize, this->algo);
}

void			Mainwindow::showModesWindow()
{
    new ModesWindow(this->mode);
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
				this->UpdateStatistics(0);
				Gomoku::GetInstance()->CommitMove(button->GetPos(), true);
                if (this->referee->CheckGame() != IN_PROGRESS)
                    this->startNewGame();
				else
					this->startMoves();
			}
		}
    }
}
