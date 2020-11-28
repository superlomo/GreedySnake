#include "GameManager.h"
#include "SnakeManager.h"
#include "CellManager.h"
#include "FoodGenerator.h"

GameManager::GameManager(QObject *parent)
	: QObject(parent)
{
	m_mainTimer.setInterval(m_updateInterval);
	connect(&m_mainTimer, &QTimer::timeout, this, &GameManager::excute);
}

GameManager::~GameManager()
{
}

void GameManager::newGame()
{
	m_cellManagerPtr.reset();
	m_snakeManagerPtr.reset();
	m_foodGeneratorPtr.reset();

	m_first = true;

	init();
}

void GameManager::init()
{
	if (!m_cellManagerPtr)
	{
		m_cellManagerPtr.reset(new CellManager(m_cellWidth, m_cellHeight));
	}

	if (!m_snakeManagerPtr)
	{
		m_snakeManagerPtr.reset(new SnakeManager());
		m_snakeManagerPtr->init(m_startLocation, m_startDirection, m_cellManagerPtr);
	}

	if (!m_foodGeneratorPtr)
	{
		m_foodGeneratorPtr.reset(new FoodGenerator());
		m_foodGeneratorPtr->init(m_cellManagerPtr, m_snakeManagerPtr);
	}
	if (m_first)
	{
		m_foodGeneratorPtr->generateNewFood();
		m_first = false;
	}
}

void GameManager::start()
{
	m_mainTimer.start();
	m_isRunning = true;
}

void GameManager::stop()
{
	m_isRunning = false;
	m_mainTimer.stop();
}

void GameManager::turn(Direction direction)
{
	if(m_isRunning)
		m_snakeManagerPtr->turn(direction);
}

void GameManager::excute()
{
	SnakeNode &headNode = m_snakeManagerPtr->getHead();
	Location nextLocation = m_cellManagerPtr->getNextLocation(headNode.m_location, headNode.m_direction);
	CellType cellType = m_cellManagerPtr->getCellTypeByLocation(nextLocation);
	if ((cellType == CellType::SnakeHead) || (cellType == CellType::SnakeBody) || (cellType == CellType::SnakeTail))
	{
		m_snakeManagerPtr->setDead();
		stop();
	}
	{
		if (cellType == CellType::Blank)
		{
			m_snakeManagerPtr->move(nextLocation);
		}
		else if (cellType == CellType::Food)
		{ 
			m_snakeManagerPtr->grow(nextLocation);
			bool winTheGame = !m_foodGeneratorPtr->generateNewFood();
			if (winTheGame)
			{

			}
		}
	}
	Q_EMIT repaint();
}
