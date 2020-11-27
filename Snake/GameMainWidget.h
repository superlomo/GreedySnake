#pragma once

#include <QWidget>
#include <qcolor.h>
#include "CellManager.h"

class GameMainWidget : public QWidget
{
	Q_OBJECT

public:
	GameMainWidget(QWidget*parent, std::shared_ptr<CellManager> cellManagerPtr);
	~GameMainWidget();

	void paintEvent(QPaintEvent* event) override;

	void paintMain();
	void paintbackground();
	void paintCell();
	void paintSnake();

private:
	const QColor m_cellColor = {255, 0, 0};
	const QColor m_backgroundColor = { 200, 200, 200 };
	std::shared_ptr<CellManager> m_cellManagerPtr;
};
