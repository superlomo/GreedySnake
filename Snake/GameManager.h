#pragma once

#include <QObject>
#include <qtimer.h>
#include <memory>
#include "GameMainWidget.h"

class SnakeManager;
class CellManager;
class FoodGenerator;

class GameManager : public QObject
{
	Q_OBJECT

public:
	GameManager(QObject *parent);
	~GameManager();

	auto getCellManager() { return m_cellManagerPtr; }
	auto getSnakeManager() { return m_snakeManagerPtr; }
	int getScore() { return m_score; }

public Q_SLOTS:
	void newGame();
	void start();
	void init();
	void stop();
	void turn(Direction direction);
	inline bool isRunning() { return m_isRunning; }

Q_SIGNALS:
	void updateSignal();

private:
	int m_updateInterval = 220; //ms
	const int m_cellWidth = 16;
	const int m_cellHeight = 16;
	const Location m_startLocation = { 8, 8 };
	const Direction m_startDirection = Direction::Top;

	QTimer m_mainTimer;
	std::shared_ptr<SnakeManager> m_snakeManagerPtr;
	std::shared_ptr<CellManager> m_cellManagerPtr;
	std::shared_ptr<FoodGenerator> m_foodGeneratorPtr;
	bool m_isRunning = false;
	bool m_first = true;
	int m_score = 0;

private Q_SLOTS:
	void excute();
};
