#include "GameManager.h"

GameManager::GameManager(QObject *parent)
	: QObject(parent)
{
	m_mainTimer.setInterval(m_updateInterval);
	connect(&m_mainTimer, &QTimer::timeout, this, &GameManager::excute);
}

GameManager::~GameManager()
{
}

void GameManager::start()
{
	m_snakeManager.init(m_startLocation, m_startDirection);
	m_mainTimer.start();
}

void GameManager::stop()
{
	m_mainTimer.stop();
}

void GameManager::turn(Direction direction)
{
	m_snakeManager.turn(direction);
}

void GameManager::excute()
{

}
