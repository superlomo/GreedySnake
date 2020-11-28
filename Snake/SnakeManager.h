#pragma once

#include <vector>
#include <memory>
#include "GlobalDefine.h"

class CellManager;

class SnakeManager
{
public:
	void init(const Location& startPoint, const Direction& direction, std::shared_ptr<CellManager> cellManagerPtr);
	void grow(Location newHeadLocation);
	void move(Location newheadLocation);
	void turn(Direction direction);
	void setDead() { m_isAlive = false; }
	bool isAlive() { return m_isAlive; }
	inline SnakeNode& getHead() { return m_snakeNodes[0]; }
	inline int getSnakeLength() { return m_snakeNodes.size(); }

private:
	void moveHead(Location newHeadLocation);
	void removeTail();

private:
	std::vector<SnakeNode> m_snakeNodes;
	std::shared_ptr<CellManager> m_cellManagerPtr;
	bool m_isAlive = true;
};

