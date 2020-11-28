#pragma once

#include <QWidget>
#include <qcolor.h>
#include "GlobalDefine.h"

class CellManager;
class SnakeManager;

class GameMainWidget : public QWidget
{
	Q_OBJECT

public:
	GameMainWidget(QWidget*parent);
	~GameMainWidget();

	void setCellManagerPtr(std::shared_ptr<CellManager> cellManagerPtr) { m_cellManagerPtr = cellManagerPtr; }
	void setSnakeManagerPtr(std::shared_ptr<SnakeManager> snakeManagerPtr) { m_snakeManagerPtr = snakeManagerPtr; }
private:
	void paintbackground(QPainter &painter);
	void paintCell(QPainter& painter);
	void paintCellBackground(QPainter& painter, Location startPoint);
	void paintSnakeHead(QPainter& painter, Location startPoint, Direction direction);
	void paintSnakeBody(QPainter& painter, Location startPoint);
	void paintFood(QPainter& painter, Location startPoint);
	
	Location getCellStartPointByIndex(int index);
	void getCellSideLengthInPixel();

private:
	const QColor m_cellColor = {200, 150, 70};
	const QColor m_backgroundColor = { 200, 200, 200 };
	const QColor m_snakeLiveColor = { 250, 80, 80 }; /*{ 100, 100, 110 };*/
	const QColor m_snakeEyeColor = { 200,200,200 };
	const QColor m_snakeDeadColor = { 255, 20, 20 };
	const QColor m_foodColor = { 80, 150, 80 };
	const int m_cellGap = 2;
	std::shared_ptr<CellManager> m_cellManagerPtr;
	std::shared_ptr<SnakeManager> m_snakeManagerPtr;
	unsigned int m_widgetWidthInPixel;
	unsigned int m_widgetHeightInPixel;
	unsigned int m_sideLengthInPixel;
	unsigned int m_cellSideLengthInPixel;

Q_SIGNALS:
	void startOrStop();
	void turn(Direction direction);

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
};
