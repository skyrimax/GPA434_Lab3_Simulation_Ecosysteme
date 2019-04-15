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

	/*Fonction qui va ajouter un terrain*/
	void addTerrain(Grid *m_grid, Environnement *environnement);
	void addHerbivore(Environnement *environnement);
	void addCarnivore(Environnement *environnement);

	Animal::Sex randomSex();//Génère un sexe aléatoire
	Coordonne randomCoordonne();//Génère une coordonné de départ


public slots:
	void simulation();


private:
	Ui::SimulationMainWindowClass ui;

	/*Timer qui sera de 30 millisecondes qui
	fera faire une boucle à chaque fois. Lorsque
	Le timer atteindre 30 millisecondes, il enverra
	Un signal*/
	QTimer mTimer;
	//Créattion de la scène
	QGraphicsScene mGraphicsScene;
	//Création d'un environnement
	Environnement *environnement;
	//Pour la grille
	Grid *m_grid;

	//Attributs pour les quantité de départ
	int mQteChevreuils;
	int mQteLapins;
	int mQteLoups;
	int mQteMeuteLoups;
	int mQteHardeChevreuil;
	

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
