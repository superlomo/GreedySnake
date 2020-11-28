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

	m_gameManager = new GameManager(this);
	m_gameManager->newGame();

	m_gameMainWidget = new GameMainWidget(this);
	ui.horizontalLayout_game->addWidget(m_gameMainWidget);
	m_gameMainWidget->setCellManagerPtr(m_gameManager->getCellManager());
	m_gameMainWidget->setSnakeManagerPtr(m_gameManager->getSnakeManager());
	
	connect(m_gameMainWidget, &GameMainWidget::startOrStop, this, [this]
		{
			bool isRunning = m_gameManager->isRunning();
			if (!isRunning)
			{
				m_gameManager->start();
			}
			else
			{
				m_gameManager->stop();
			}
		});
	connect(m_gameMainWidget, &GameMainWidget::turn, m_gameManager, &GameManager::turn);

	connect(m_gameManager, &GameManager::updateSignal, this, [this]
		{
			m_controlBoard->setScore(m_gameManager->getScore());
			m_gameMainWidget->repaint();
		});
	m_soundManager = new SoundManager(this);
	m_soundManager->playBackgroundMusic();

	m_controlBoard = new ControlBoard(this, &ui);
}

MainWindow::~MainWindow()
{
}
