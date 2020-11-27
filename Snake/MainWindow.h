#pragma once

#include <QWidget>
#include "ui_MainWindow.h"

class GameMainWidget;
class GameManager;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindow ui;
	GameMainWidget* m_gameMainWidget = nullptr;
	GameManager* m_gameManager = nullptr;
};
