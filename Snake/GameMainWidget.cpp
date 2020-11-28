#include "GameMainWidget.h"
#include <qpainter.h>
#include <qevent.h>
#include <qbrush.h>
#include <qpen.h>
#include "CellManager.h"
#include "SnakeManager.h"
#include "GameManager.h"
#include <cmath>

GameMainWidget::GameMainWidget(QWidget*parent)
	: QWidget(parent)
{
	this->grabKeyboard();
}

GameMainWidget::~GameMainWidget()
{
}

void GameMainWidget::paintEvent(QPaintEvent* event)
{
	if (m_cellManagerPtr)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		m_widgetWidthInPixel = this->width();
		m_widgetHeightInPixel = this->height();

		getCellSideLengthInPixel();

		paintbackground(painter);
		paintCell(painter);
		if(m_gameManagerPtr->getGameStatus() != GameStatus::Running)
			paintStopIcon(painter);
	}
}

void GameMainWidget::getCellSideLengthInPixel()
{
	Size cellsSize = m_cellManagerPtr->getCellsSize();
	m_cellSideLengthInPixel = (m_widgetWidthInPixel - (cellsSize.x - 1) * m_cellGap) / cellsSize.x;
	int calculatedHeight = m_cellSideLengthInPixel * cellsSize.y + (cellsSize.y - 1) * m_cellGap;
	if (calculatedHeight > m_widgetHeightInPixel)
		m_cellSideLengthInPixel = (m_widgetHeightInPixel - (cellsSize.y - 1) * m_cellGap) / cellsSize.y;
}

void GameMainWidget::paintbackground(QPainter& painter)
{
	painter.setBrush(m_backgroundColor);
	painter.setPen(m_backgroundColor);
	painter.drawRect(0, 0, m_widgetWidthInPixel, m_widgetHeightInPixel);
}

void GameMainWidget::paintCell(QPainter& painter)
{
	int index = 0;
	for (Cell& cell : m_cellManagerPtr->getCells())
	{
		Location startPoint = getCellStartPointByIndex(index);
		paintCellBackground(painter, startPoint);
		if (cell.type == CellType::SnakeHead)
			paintSnakeHead(painter, startPoint, m_snakeManagerPtr->getHead().m_direction);
		else if (cell.type == CellType::SnakeBody)
			paintSnakeBody(painter, startPoint);
		else if (cell.type == CellType::SnakeTail)
			paintSnakeBody(painter, startPoint);
		else if (cell.type == CellType::Food)
			paintFood(painter, startPoint);
		index++;
	}
}

void GameMainWidget::paintCellBackground(QPainter& painter, Location startPoint)
{
	painter.setBrush(m_cellColor);
	painter.setPen(m_cellColor);
	painter.drawRect(startPoint.x, startPoint.y, m_cellSideLengthInPixel, m_cellSideLengthInPixel);
}

void GameMainWidget::paintSnakeHead(QPainter& painter, Location startPoint, Direction direction)
{
	QColor snakeColor = m_snakeManagerPtr->isAlive() ? m_snakeLiveColor : m_snakeDeadColor;
	painter.setBrush(snakeColor);
	QPen pen;
	pen.setWidth(1);
	pen.setColor(snakeColor);
	painter.setPen(pen);
	QRectF rectangle(startPoint.x, startPoint.y, m_cellSideLengthInPixel, m_cellSideLengthInPixel);
	QRectF headRect = rectangle;
	int startAngle = 0;
	if (direction == Direction::Top)
	{
		startAngle = 0;
		headRect.setY(startPoint.y + m_cellSideLengthInPixel / 2);
		headRect.setHeight(m_cellSideLengthInPixel / 2);
	}
	else if (direction == Direction::Left)
	{
		startAngle = 90 * 16;
		headRect.setX(startPoint.x + m_cellSideLengthInPixel / 2);
		headRect.setWidth(m_cellSideLengthInPixel / 2);
	}
	else if (direction == Direction::Right)
	{
		startAngle = 270 * 16;
		headRect.setWidth(m_cellSideLengthInPixel / 2);
	}
	else if (direction == Direction::Down)
	{
		startAngle = 180 * 16;		
		headRect.setHeight(m_cellSideLengthInPixel / 2);
	}
	int spanAngle = 180 * 16;
	painter.drawPie(rectangle, startAngle, spanAngle);
	painter.drawRect(headRect);

	painter.setBrush(m_snakeEyeColor);
	painter.drawEllipse(QPoint(startPoint.x + m_cellSideLengthInPixel / 2, startPoint.y + m_cellSideLengthInPixel / 2), 3, 3);
}

void GameMainWidget::paintSnakeBody(QPainter& painter, Location startPoint)
{
	QColor snakeColor = m_snakeManagerPtr->isAlive() ? m_snakeLiveColor : m_snakeDeadColor;
	painter.setBrush(snakeColor);
	QPen pen;
	pen.setWidth(1);
	pen.setColor(snakeColor);
	painter.setPen(pen);
	painter.drawRect(startPoint.x, startPoint.y, m_cellSideLengthInPixel, m_cellSideLengthInPixel);
}

void GameMainWidget::paintFood(QPainter& painter, Location startPoint)
{
	painter.setBrush(m_foodColor);
	QPen pen;
	pen.setWidth(1);
	pen.setColor(m_foodColor);
	painter.setPen(pen);
	QRectF rectangle(startPoint.x, startPoint.y, m_cellSideLengthInPixel, m_cellSideLengthInPixel);
	painter.drawEllipse(rectangle);
}

void GameMainWidget::paintStopIcon(QPainter& painter)
{
	painter.setPen(QColor(100, 100, 100, 100));
	painter.setBrush(QColor(100, 100, 100, 100));
	painter.drawEllipse(QPoint(m_widgetWidthInPixel / 2, m_widgetHeightInPixel / 2), 40, 40);

	painter.setPen(QColor(50, 50, 50, 100));
	painter.setBrush(QColor(50, 50, 50, 100));
	const int triangleOutterCircleSemiDiameter = 30;
	std::vector<QPointF> points = {
		QPointF(m_widgetWidthInPixel / 2 + triangleOutterCircleSemiDiameter, m_widgetHeightInPixel / 2),
		QPointF(m_widgetWidthInPixel / 2 - triangleOutterCircleSemiDiameter / 2, m_widgetHeightInPixel / 2 + triangleOutterCircleSemiDiameter / 2 * std::sqrt(3)),
		QPointF(m_widgetWidthInPixel / 2 - triangleOutterCircleSemiDiameter / 2, m_widgetHeightInPixel / 2 - triangleOutterCircleSemiDiameter / 2 * std::sqrt(3))};
	painter.drawPolygon(points.data(), 3);
}

Location GameMainWidget::getCellStartPointByIndex(int index)
{
	Location startPoint;
	Size cellSize = m_cellManagerPtr->getCellsSize();
	Location location = m_cellManagerPtr->getLocationByIndex(index);
	startPoint.x =(m_widgetWidthInPixel - (cellSize.x * m_cellSideLengthInPixel + (cellSize.x - 1) * m_cellGap)) / 2 +
		location.x * m_cellSideLengthInPixel + location.x * m_cellGap;
	startPoint.y = (m_widgetHeightInPixel - (cellSize.y * m_cellSideLengthInPixel + (cellSize.y - 1) * m_cellGap)) / 2 +
		location.y * m_cellSideLengthInPixel + location.y * m_cellGap;
	return startPoint;
}

void GameMainWidget::keyPressEvent(QKeyEvent* event)
{
	Direction direction = Direction::Undefined;
	if ((event->key() == Qt::Key_W) || (event->key() == Qt::Key_Up))
		direction = Direction::Top;
	else if ((event->key() == Qt::Key_A) || (event->key() == Qt::Key_Left))
		direction = Direction::Left;
	else if ((event->key() == Qt::Key_D) || (event->key() == Qt::Key_Right))
		direction = Direction::Right;
	else if ((event->key() == Qt::Key_S) || (event->key() == Qt::Key_Down))
		direction = Direction::Down;
	
	if (direction != Direction::Undefined)
	{
		Q_EMIT turn(direction);
	}

	if ((event->key() == Qt::Key_Escape) || (event->key() == Qt::Key_Space))
		Q_EMIT startOrStop();
}
