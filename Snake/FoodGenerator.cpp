#include "FoodGenerator.h"
#include "CellManager.h"
#include "SnakeManager.h"
#include <iostream>
#include <chrono>

FoodGenerator::FoodGenerator()
{
	m_randomEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

void FoodGenerator::init(std::shared_ptr<CellManager> cellManagerPtr, std::shared_ptr<SnakeManager> snakeManagerPtr)
{
	m_cellManagerPtr = cellManagerPtr;
	m_snakeManagerPtr = snakeManagerPtr;
}

bool FoodGenerator::generateNewFood()
{
	std::vector<Cell>& cells = m_cellManagerPtr->getCells();
	int blanckCellCounts = cells.size() - m_snakeManagerPtr->getSnakeLength();
	if (blanckCellCounts)
	{
		int choosenIndex = m_randomEngine() % blanckCellCounts;

		int i = 0;
		for (auto& cell : cells)
		{
			if (cell.type == CellType::Blank)
			{
				if (i == choosenIndex)
					cell.type = CellType::Food;
				i++;
			}
		}
		return true;
	}
	else
		return false;
}
