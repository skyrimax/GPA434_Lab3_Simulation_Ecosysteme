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


private slots:
	//Slots pour afficher le "À propos" du programme de simullation
	void showAPropos();

	//Slots pour aller définir les paramètre de simulation
	void on_parameterButton_clicked();
};
