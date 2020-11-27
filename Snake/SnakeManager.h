#pragma once

#include <vector>
#include "GlobalDefine.h"

class SnakeManager
{
public:
	void init(const Location& startPoint, const Direction& direction);
	void grow(Location newHeadLocation);
	void move(Location newheadLocation);
	void turn(Direction direction);
	inline Direction getHeadDirection();

private:
	void moveHead(Location newHeadLocation);
	void removeTail();

private:
	std::vector<SnakeNode> m_snakeNodes;
};

