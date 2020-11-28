#include "ControlBoard.h"
#include "ui_MainWindow.h"

ControlBoard::ControlBoard(QObject *parent, Ui::MainWindow* ui)
	: QObject(parent),
	m_ui(ui)
{
}

ControlBoard::~ControlBoard()
{
}

void ControlBoard::setScore(int score)
{
	m_ui->label_score->setText(QString::number(score));
}
