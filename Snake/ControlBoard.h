#pragma once

#include <QObject>

namespace Ui
{
	class MainWindow;
}

class ControlBoard : public QObject
{
	Q_OBJECT

public:
	ControlBoard(QObject *parent, Ui::MainWindow *ui);
	~ControlBoard();

	void setScore(int score);

private:
	Ui::MainWindow* m_ui;
};
