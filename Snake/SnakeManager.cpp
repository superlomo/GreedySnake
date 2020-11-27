#include "SnakeManager.h"

void SnakeManager::init(const Location& startPoint, const Direction& direction)
{
	m_snakeNodes.emplace_back(direction, NodeType::Head, startPoint);
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
	m_snakeNodes.at(0).m_direction = direction;
}

inline Direction SnakeManager::getHeadDirection()
{
	return m_snakeNodes[0].m_direction;
}

void SnakeManager::moveHead(Location newHeadLocation)
{
	SnakeNode node = { m_snakeNodes[0].m_direction, NodeType::Head, std::move(newHeadLocation) };
	m_snakeNodes[0].m_type = NodeType::Body;
	int size = m_snakeNodes.size();
	if (size > 2)
		m_snakeNodes[m_snakeNodes.size() - 2].m_type = NodeType::Tail;
	m_snakeNodes.insert(m_snakeNodes.begin(), std::move(node));
}

void SnakeManager::removeTail()
{
	m_snakeNodes.erase(m_snakeNodes.end());
}
