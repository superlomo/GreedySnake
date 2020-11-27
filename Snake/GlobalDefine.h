#pragma once

enum CellType
{
	Blank,

	SnakeHead,
	SnakeBody,
	SnakeTail,
	
	Food,
};

enum Direction
{
	Left,
	Right,
	Top,
	Bottom
};

enum NodeType
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