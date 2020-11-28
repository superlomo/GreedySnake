#pragma once

#include <QWidget>
#include "ui_MainWindow.h"

class GameMainWidget;
class GameManager;
class SoundManager;
class ControlBoard;

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
	SoundManager* m_soundManager = nullptr;
	ControlBoard *m_controlBoard = nullptr;
};
