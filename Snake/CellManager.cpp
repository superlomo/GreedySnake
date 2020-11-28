#include "CellManager.h"

CellManager::CellManager(int width, int height):
	m_width(width),
	m_height(height)
{
	m_cells.resize(width * height);
}

Location CellManager::getNextLocation(Location location, Direction direction)
{
	if (direction == Direction::Left)
	{
		if (location.x == 0)
			location.x = m_width - 1;
		else
			location.x--;
	}
	else if (direction == Direction::Right)
	{
		if (location.x == (m_width - 1))
			location.x = 0;
		else
			location.x++;
	}
	else if (direction == Direction::Top)
	{
		if (location.y == 0)
			location.y = m_height - 1;
		else
			location.y--;
	}
	else if (direction == Direction::Down)
	{
		if (location.y == (m_height - 1))
			location.y = 0;
		else
			location.y++;
	}
	return location;
}

CellType CellManager::getCellTypeByLocation(Location location)
{
	return m_cells[location.y * m_width + location.x].type;
}

void CellManager::updateCellTypeByLocation(Location location, CellType cellType)
{
	m_cells[location.y * m_width + location.x].type = cellType;
}

int CellManager::getIndexByLocation(Location location)
{
	return (location.y - 1) * m_width + location.x;
}

Location CellManager::getLocationByIndex(int index)
{
	Location location;
	location.y = index / m_width;
	location.x = index % m_width;
	return location;
}
