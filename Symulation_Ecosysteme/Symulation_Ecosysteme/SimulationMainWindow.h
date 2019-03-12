#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulationMainWindow.h"

class SimulationMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SimulationMainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::SimulationMainWindowClass ui;
};
