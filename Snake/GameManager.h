#pragma once

#include <QObject>
#include <qtimer.h>
#include <memory>
#include "SnakeManager.h"
#include "GameMainWidget.h"
#include "CellManager.h"

class GameManager : public QObject
{
	Q_OBJECT

public:
	GameManager(QObject *parent);
	~GameManager();

	void start();
	void stop();
	auto getCellManager() { return m_cellManagerPtr; }

public Q_SLOTS:
	void turn(Direction direction);

private:
	int m_updateInterval = 200; //ms
	static const int m_cellWidth = 64;
	static const int m_cellHeight = 64;
	const Location m_startLocation = { 31, 31 };
	const Direction m_startDirection = Direction::Top;

	QTimer m_mainTimer;
	SnakeManager m_snakeManager;
	GameMainWidget *m_gameMainWidget;
	std::shared_ptr<CellManager> m_cellManagerPtr;

private Q_SLOTS:
	void excute();
};
