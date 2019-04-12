#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_SimulationMainWindow.h"
#include "ParameterWindow.h"
#include "ClassesSimulateur/Environement.h"
#include "ClassesSimulateur/Sex.h"

class ParameterWindow;

class SimulationMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SimulationMainWindow(QWidget *parent = Q_NULLPTR);


private:
	Ui::SimulationMainWindowClass ui;
	Animal::Sex randomSex();
	Coordonne randomCoordonne();

	Grid *m_grid;
	/*Timer qui sera de 30 millisecondes qui
	fera faire une boucle � chaque fois. Lorsque
	Le timer atteindre 30 millisecondes, il enverra
	Un signal*/
	QTimer mTimer;
	//Cr�attion de la sc�ne
	QGraphicsScene mGraphicsScene;
	//Cr�ation d'un environnement
	Environnement *environnement;

	ParameterWindow *mparameter;

	
private slots:
	//Slots pour afficher le "� propos" du programme de simullation
	void showAPropos();
	//Slots pour aller d�finir les param�tre de simulation
	void on_parameterButton_clicked();
	//Slots pour d�marrer la simulation
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
