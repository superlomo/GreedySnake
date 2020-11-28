#pragma once

#include <memory>

class SnakeManager;
class CellManager;

class FoodGenerator
{
public:
	void init(std::shared_ptr<CellManager> cellManagerPtr, std::shared_ptr<SnakeManager> snakeManagerPtr);
	void generateNewFood();

private:
	std::shared_ptr<CellManager> m_cellManagerPtr;
	std::shared_ptr<SnakeManager> m_snakeManagerPtr;
};

