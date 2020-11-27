#pragma once

#include "GlobalDefine.h"
#include <array>

class CellManager
{
public:
	CellManager(int width, int height):
		m_width(width),
		m_height(height)
	{
		m_cells.resize(width * height);
		std::transform(m_cells.begin(), m_cells.end(), m_cells.begin(), [](CellType)->CellType { return CellType::Blank; });
	}

private:
	std::vector<CellType> m_cells;
	int m_width;
	int m_height;

private:
	int locationToIndex(Location location) 
	{ 
		return (location.y - 1) * m_width + location.x; 
	}
};

