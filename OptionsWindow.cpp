#include "Images/valid.xpm"
#include "Images/cancel.xpm"
#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(int boardSize)
{
    this->boardSize = boardSize;
    this->setWindowTitle("Options");
    this->moveToCenter();
    this->setMinimumSize(OPTIONSWINDOW_WIDTH, OPTIONSWINDOW_HEIGHT);
    this->setMaximumSize(OPTIONSWINDOW_WIDTH, OPTIONSWINDOW_HEIGHT);

    this->generalLayout = new QGridLayout(this);
    this->groupBox = new QGroupBox("Players", this);

    this->playerLayout = new QGridLayout(groupBox);
    this->l_player1 = new QLabel("Player 1 :", this->groupBox);
    this->cb_player1 = new QComboBox(this->groupBox);
    this->cb_player1->setObjectName("cb_player1");
    this->cb_player1->addItem("Human");
    this->cb_player1->addItem("IA");
    this->cb_player1Algo = new QComboBox(this->groupBox);
    this->cb_player1Algo->addItem("AlphaBeta");
    this->cb_player1Algo->addItem("NegaMax");
    this->cb_player1Algo->setEnabled(false);

    this->l_player2 = new QLabel("Player 2 :", this->groupBox);
    this->cb_player2 = new QComboBox(this->groupBox);
    this->cb_player2->setObjectName("cb_player2");
    this->cb_player2->addItem("Human");
    this->cb_player2->addItem("IA");
    this->cb_player2Algo = new QComboBox(this->groupBox);
    this->cb_player2Algo->addItem("AlphaBeta");
    this->cb_player2Algo->addItem("NegaMax");
    this->cb_player2Algo->setEnabled(false);
    this->playerLayout->addWidget(this->l_player1, 0, 0, 1, 1);
    this->playerLayout->addWidget(this->cb_player1, 0, 1, 1, 1);
    this->playerLayout->addWidget(this->cb_player1Algo, 0, 2, 1, 1);
    this->playerLayout->addWidget(this->l_player2, 1, 0, 1, 1);
    this->playerLayout->addWidget(this->cb_player2, 1, 1, 1, 1);
    this->playerLayout->addWidget(this->cb_player2Algo, 1, 2, 1, 1);

    this->generalLayout->addWidget(this->groupBox, 0, 0, 1, 2);

    this->groupBoxRules = new QGroupBox("Rules", this);
    this->rulesLayout = new QVBoxLayout(this->groupBoxRules);
    this->cb_checkDoubleThree = new QCheckBox("Double three", this->groupBoxRules);
    this->cb_checkDoubleThree->setCheckState(Qt::Checked);
    this->cb_checkAlternativeEndGame = new QCheckBox("Alternative end game", this->groupBoxRules);
    this->cb_checkAlternativeEndGame->setCheckState(Qt::Checked);
    this->rulesLayout->addWidget(this->cb_checkDoubleThree);
    this->rulesLayout->addWidget(this->cb_checkAlternativeEndGame);
    this->generalLayout->addWidget(this->groupBoxRules, 1, 0, 1, 2);


    this->l_boardSize = new QLabel("Board size", this);
    this->generalLayout->addWidget(this->l_boardSize, 2, 0, 1, 1);

    this->spinBox_boardSize = new QSpinBox(this);
    this->spinBox_boardSize->setMinimum(MIN);
    this->spinBox_boardSize->setMaximum(this->getMaxBoardSize() < MAX ? this->getMaxBoardSize() : MAX);
    this->spinBox_boardSize->setValue(boardSize);
    this->generalLayout->addWidget(this->spinBox_boardSize, 2, 1, 1, 1);

    this->button_valid = new QPushButton("Valid", this);
    this->button_valid->setIcon(QIcon(QPixmap(valid_xpm)));
    this->generalLayout->addWidget(this->button_valid, 3, 0, 1, 1);

    this->button_cancel = new QPushButton("Cancel", this);
    this->button_cancel->setIcon(QIcon(QPixmap(cancel_xpm)));
    this->generalLayout->addWidget(this->button_cancel, 3, 1, 1, 1);

    this->doConnects();
    this->loadPreviousConfig();
    this->show();
}

void    OptionsWindow::loadPreviousConfig()
{
    if (Gomoku::GetInstance()->GetPlayer(PLAYER1)->GetType() == IS_IA_ALPHABETA)
    {
        this->cb_player1->setCurrentIndex(1);
        this->cb_player1Algo->setEnabled(true);
    }
    else if (Gomoku::GetInstance()->GetPlayer(PLAYER1)->GetType() == IS_IA_NEGAMAX)
    {
        this->cb_player1->setCurrentIndex(1);
        this->cb_player1Algo->setCurrentIndex(1);
        this->cb_player1Algo->setEnabled(true);
    }
    if (Gomoku::GetInstance()->GetPlayer(PLAYER2)->GetType() == IS_IA_ALPHABETA)
    {
        this->cb_player2->setCurrentIndex(1);
        this->cb_player2Algo->setEnabled(true);
    }
    else if (Gomoku::GetInstance()->GetPlayer(PLAYER2)->GetType() == IS_IA_NEGAMAX)
    {
        this->cb_player2->setCurrentIndex(1);
        this->cb_player2Algo->setCurrentIndex(1);
        this->cb_player2Algo->setEnabled(true);
    }
    this->cb_checkDoubleThree->setCheckState(Gomoku::GetInstance()->GetRuleDoubleThree() ? Qt::Checked : Qt::Unchecked);
    this->cb_checkAlternativeEndGame->setCheckState(Gomoku::GetInstance()->GetRuleAlternativeEndGame() ? Qt::Checked : Qt::Unchecked);
}

void    OptionsWindow::moveToCenter()
{
    this->move(Mainwindow::GetInstance()->x() + Mainwindow::GetInstance()->width() / 2 - this->width() / 4,
               Mainwindow::GetInstance()->y() + Mainwindow::GetInstance()->height() / 2 - this->height() / 4);
}

int    OptionsWindow::getMaxBoardSize()
{
   return ((this->desktop.screenGeometry().height() - MENU_HEIGHT * 2) / DEFAULT_BUTTONSIZE);
}

void    OptionsWindow::doConnects()
{
    connect(this->button_valid, SIGNAL(clicked()), this, SLOT(valid()));
    connect(this->button_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(this->cb_player1, SIGNAL(currentIndexChanged(int)), this, SLOT(changingPlayer()));
    connect(this->cb_player2, SIGNAL(currentIndexChanged(int)), this, SLOT(changingPlayer()));
}

void            OptionsWindow::changingPlayer()
{
    QComboBox   *comboBox = dynamic_cast<QComboBox *>(sender());

    if (comboBox)
    {
        if (comboBox->objectName() == "cb_player1" && comboBox->itemText(comboBox->currentIndex()) == "IA")
            this->cb_player1Algo->setEnabled(true);
        else if (comboBox->objectName() == "cb_player2" && comboBox->itemText(comboBox->currentIndex()) == "IA")
            this->cb_player2Algo->setEnabled(true);
        else if (comboBox->objectName() == "cb_player1")
            this->cb_player1Algo->setEnabled(false);
        else
            this->cb_player2Algo->setEnabled(false);
    }
}

void    OptionsWindow::savePlayerType(PlayerNumber playerNum, QComboBox* player, QComboBox* algo)
{
    if (player->itemText(player->currentIndex()) == "IA")
    {
        if (algo->itemText(algo->currentIndex()) == "AlphaBeta")
            Gomoku::GetInstance()->SetPlayer(playerNum, IS_IA_ALPHABETA);
        else
            Gomoku::GetInstance()->SetPlayer(playerNum, IS_IA_NEGAMAX);
    }
    else
            Gomoku::GetInstance()->SetPlayer(playerNum, IS_HUMAN);
}

void        OptionsWindow::valid()
{
    this->savePlayerType(PLAYER1, this->cb_player1, this->cb_player1Algo);
    this->savePlayerType(PLAYER2, this->cb_player2, this->cb_player2Algo);
    if (this->boardSize != this->spinBox_boardSize->value())
    {
        Mainwindow::GetInstance()->SetBoardSize(this->spinBox_boardSize->value());
        Mainwindow::GetInstance()->CreateBoard();
    }
    Gomoku::GetInstance()->SetRules(this->cb_checkDoubleThree->checkState() == Qt::Checked,
                                    this->cb_checkAlternativeEndGame->checkState() == Qt::Checked);
    if (Mainwindow::GetInstance()->checkGameState() != IN_PROGRESS)
        Mainwindow::GetInstance()->startNewGame();
    Mainwindow::GetInstance()->GetStatistics()->Reset();
    if ((Gomoku::GetInstance()->GetPlayer(PLAYER1)->GetType() == IS_IA_ALPHABETA ||
         Gomoku::GetInstance()->GetPlayer(PLAYER1)->GetType() == IS_IA_NEGAMAX) ||
         (Gomoku::GetInstance()->GetPlayer(PLAYER2)->GetType() == IS_IA_ALPHABETA ||
         Gomoku::GetInstance()->GetPlayer(PLAYER2)->GetType() == IS_IA_NEGAMAX))
    {
        Mainwindow::GetInstance()->StartMoves();
    }
    delete this;
}

void    OptionsWindow::cancel()
{
    delete this;
}

OptionsWindow::~OptionsWindow()
{
    delete this->l_player1;
    delete this->cb_player1;
    delete this->cb_player1Algo;
    delete this->l_player2;
    delete this->cb_player2;
    delete this->cb_player2Algo;
    delete this->playerLayout;
    delete this->groupBox;
    delete this->cb_checkDoubleThree;
    delete this->cb_checkAlternativeEndGame;
    delete this->rulesLayout;
    delete this->groupBoxRules;
    delete this->l_boardSize;
    delete this->spinBox_boardSize;
    delete this->button_valid;
    delete this->button_cancel;
    delete this->generalLayout;
}
