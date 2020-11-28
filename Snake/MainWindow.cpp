#include "MainWindow.h"
#include "GameMainWidget.h"
#include "GameManager.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_gameManager = new GameManager(this);

	m_gameMainWidget = new GameMainWidget(this);
	ui.horizontalLayout_game->addWidget(m_gameMainWidget);
	
	connect(m_gameMainWidget, &GameMainWidget::startOrStop, this, [this]
		{
			bool isRunning = m_gameManager->isRunning();
			if (!isRunning)
			{
				m_gameManager->start();
				m_gameMainWidget->setCellManagerPtr(m_gameManager->getCellManager());
				m_gameMainWidget->setSnakeManagerPtr(m_gameManager->getSnakeManager());
			}
			else
			{
				m_gameManager->stop();
			}
		});
	connect(m_gameMainWidget, &GameMainWidget::turn, m_gameManager, &GameManager::turn);

	connect(m_gameManager, &GameManager::repaint, m_gameMainWidget, [this]
		{
			m_gameMainWidget->repaint();
		});
}

MainWindow::~MainWindow()
{
}
