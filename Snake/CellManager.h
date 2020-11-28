#pragma once

#include "GlobalDefine.h"
#include <vector>
#include <algorithm>

class CellManager
{
public:
	CellManager(int width, int height);

	inline std::vector<Cell>& getCells() { return m_cells; }
	Location getNextLocation(Location location, Direction direction);
	CellType getCellTypeByLocation(Location location);
	void updateCellTypeByLocation(Location location, CellType cellType);
	Size getCellsSize() { return Size{ m_width, m_height }; }
	int getIndexByLocation(Location location);
	Location getLocationByIndex(int index);

private:
	std::vector<Cell> m_cells;
	unsigned int m_width;
	unsigned int m_height;
};

