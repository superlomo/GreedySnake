#include "GameMainWidget.h"
#include <qpainter.h>

GameMainWidget::GameMainWidget(QWidget*parent, std::shared_ptr<CellManager> cellManagerPtr)
	: QWidget(parent),
	m_cellManagerPtr(cellManagerPtr)
{
}

GameMainWidget::~GameMainWidget()
{
}

void GameMainWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
}

void GameMainWidget::paintMain()
{
}

void GameMainWidget::paintbackground()
{
}

void GameMainWidget::paintCell()
{
}

void GameMainWidget::paintSnake()
{
}
