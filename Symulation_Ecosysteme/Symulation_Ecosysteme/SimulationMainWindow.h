#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulationMainWindow.h"
#include "ParameterWindow.h"

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
	//Slots pour démarrer la simulation
	void on_startButton_clicked();
	//Slots pour mettre sur pause la simulation
	void on_pauseButton_clicked();
	//Slots pour continuer la simulation
	void on_resumButton_clicked();
	//Slots pour faire du step be step 
	void on_stepButton_clicked();
	//Slots pour terminer la simulation
	void on_stopButton_clicked();
};
