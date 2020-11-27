#include "MainWindow.h"
#include "GameMainWidget.h"
#include "GameManager.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_gameManager = new GameManager(this);

	m_gameMainWidget = new GameMainWidget(this, m_gameManager->getCellManager());
	ui.horizontalLayout_game->addWidget(m_gameMainWidget);
}

MainWindow::~MainWindow()
{
}
