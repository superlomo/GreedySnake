#include "SnakeManager.h"
#include "CellManager.h"

void SnakeManager::init(const Location& startPoint, const Direction& direction, std::shared_ptr<CellManager> cellManagerPtr)
{
	m_snakeNodes.emplace_back(direction, NodeType::Head, startPoint);
	m_cellManagerPtr = cellManagerPtr;
	m_cellManagerPtr->updateCellTypeByLocation(startPoint, CellType::SnakeHead);
	m_isAlive = true;
}

void SnakeManager::grow(Location newHeadLocation)
{
	moveHead(newHeadLocation);
}

void SnakeManager::move(Location newHeadLocation)
{
	moveHead(newHeadLocation);
	removeTail();
}

void SnakeManager::turn(Direction direction)
{
	if (m_snakeNodes.size() >= 2)
	{
		Location location = m_cellManagerPtr->getNextLocation(m_snakeNodes.at(0).m_location, direction);
		auto &previousNode = m_snakeNodes.at(1);
		if ((location.x == previousNode.m_location.x) &&
			(location.y == previousNode.m_location.y))
			return;
	}
	m_snakeNodes.at(0).m_direction = direction;
}

void SnakeManager::moveHead(Location newHeadLocation)
{
	m_cellManagerPtr->updateCellTypeByLocation(newHeadLocation, CellType::SnakeHead);
	m_cellManagerPtr->updateCellTypeByLocation(m_snakeNodes[0].m_location, CellType::SnakeBody);

	SnakeNode node = { m_snakeNodes[0].m_direction, NodeType::Head, std::move(newHeadLocation) };
	m_snakeNodes[0].m_type = NodeType::Body;
	m_snakeNodes.insert(m_snakeNodes.begin(), std::move(node));
}

void SnakeManager::removeTail()
{
	int size = m_snakeNodes.size();
	if (size > 2)
	{
		m_snakeNodes[m_snakeNodes.size() - 2].m_type = NodeType::Tail;
		m_cellManagerPtr->updateCellTypeByLocation(m_snakeNodes[m_snakeNodes.size() - 2].m_location, CellType::SnakeTail);
	}
	m_cellManagerPtr->updateCellTypeByLocation(m_snakeNodes.back().m_location, CellType::Blank);
	m_snakeNodes.erase(m_snakeNodes.end()- 1);
}
