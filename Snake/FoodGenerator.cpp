#include "FoodGenerator.h"
#include <random>
#include "CellManager.h"
#include "SnakeManager.h"

void FoodGenerator::init(std::shared_ptr<CellManager> cellManagerPtr, std::shared_ptr<SnakeManager> snakeManagerPtr)
{
	m_cellManagerPtr = cellManagerPtr;
	m_snakeManagerPtr = snakeManagerPtr;
}

void FoodGenerator::generateNewFood()
{
	std::default_random_engine randomEngine;
	std::vector<Cell>& cells = m_cellManagerPtr->getCells();
	int choosenIndex = randomEngine() % (cells.size() - m_snakeManagerPtr->getSnakeLength());
	
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
}
