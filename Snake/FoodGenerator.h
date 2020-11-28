#pragma once

#include <memory>
#include <random>

class SnakeManager;
class CellManager;

class FoodGenerator
{
public:
	FoodGenerator();
	void init(std::shared_ptr<CellManager> cellManagerPtr, std::shared_ptr<SnakeManager> snakeManagerPtr);
	bool generateNewFood();

private:
	std::shared_ptr<CellManager> m_cellManagerPtr;
	std::shared_ptr<SnakeManager> m_snakeManagerPtr;
	std::default_random_engine m_randomEngine;
};

