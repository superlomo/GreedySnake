#include "MainWindow.h"
#include "GameMainWidget.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "ControlBoard.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle("GreedySnake");

	m_gameManagerPtr.reset(new GameManager);
	m_gameManagerPtr->newGame();

	m_gameMainWidget = new GameMainWidget(this);
	ui.horizontalLayout_game->addWidget(m_gameMainWidget);
	m_gameMainWidget->setCellManagerPtr(m_gameManagerPtr->getCellManager());
	m_gameMainWidget->setSnakeManagerPtr(m_gameManagerPtr->getSnakeManager());
	m_gameMainWidget->setGameManagerPtr(m_gameManagerPtr);
	
	connect(m_gameMainWidget, &GameMainWidget::startOrStop, this, [this]
		{
			GameStatus gameStatus = m_gameManagerPtr->getGameStatus();
			if ((gameStatus == GameStatus::Losed) || (gameStatus == GameStatus::Winned))
			{
				m_gameManagerPtr->newGame();
				m_gameMainWidget->setCellManagerPtr(m_gameManagerPtr->getCellManager());
				m_gameMainWidget->setSnakeManagerPtr(m_gameManagerPtr->getSnakeManager());
				m_gameManagerPtr->start();
			}
			else if (gameStatus == GameStatus::Running)
			{
				m_gameManagerPtr->stop();
			}
			else if (gameStatus == GameStatus::Unstarted)
			{
				m_gameManagerPtr->start();
			}
		});
	connect(m_gameMainWidget, &GameMainWidget::turn, m_gameManagerPtr.get(), &GameManager::turn);

	connect(m_gameManagerPtr.get(), &GameManager::updateSignal, this, [this]
		{
			m_controlBoard->setScore(m_gameManagerPtr->getScore());
			m_gameMainWidget->repaint();
		});
	m_soundManager = new SoundManager(this);
	m_soundManager->playBackgroundMusic();

	m_controlBoard = new ControlBoard(this, &ui);
}

MainWindow::~MainWindow()
{
}
