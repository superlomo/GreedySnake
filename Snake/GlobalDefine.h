#pragma once

enum class CellType
{
	Blank,

	SnakeHead,
	SnakeBody,
	SnakeTail,
	
	Food,
};

struct Cell
{
	CellType type = CellType::Blank;
};

enum class Direction
{
	Undefined,
	Left,
	Right,
	Top,
	Down
};

enum class NodeType
{
	Head,
	Body,
	Tail
};

struct Location
{
	unsigned int x;
	unsigned int y;
};

using Size = Location;

struct SnakeNode
{
	Direction m_direction;
	NodeType m_type;
	Location m_location;
	SnakeNode(Direction direction, NodeType type, Location location):
		m_direction(direction),
		m_type(type),
		m_location(location)
	{}
};