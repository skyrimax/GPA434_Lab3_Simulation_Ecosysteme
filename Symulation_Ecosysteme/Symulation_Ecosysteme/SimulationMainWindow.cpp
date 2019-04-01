#include "stdafx.h"
#include "SimulationMainWindow.h"
#include "ParameterWindow.h"

SimulationMainWindow::SimulationMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*Désactivation des boutons de la simulation afin
	que l'utilisateur rentre ses paramètres avant*/
	ui.pauseButton->setEnabled(false);
	ui.resumeButton->setEnabled(false);
	ui.stepButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	/*Connection entre le mTimer et la fonction qui va simuler l'écosystème,
	à chaque 30 millisecondes, un signal sera "envoyé" vers la fonction
	afin de mettre à jour les positions et les états.*/
	connect(&mTimer, &QTimer::timeout, environnement, &Environnement::simulation);
	}

void SimulationMainWindow::showAPropos()
{
	//Créer le message
	QString aboutProgramm{ \
	u8R"---(EcoSimulated est un logiciel de simulation d'un écosystème incluant
 les plantes, lapins, chevreuils et loups.

Ce programme a été réalisé par :
	- Frédéric Grondines
	- Guillaume Faucher
	- Mathieu Labelle
	- Maxime Royal
	- Mikaël Valton Charette

Dans le cadre du cours :
	- GPA434 - Ingénierie des systèmes orientés-objet
	- Laboratoire 3

Version 1.0)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(À propos)", aboutProgramm);
}

void SimulationMainWindow::on_parameterButton_clicked()
{
	ParameterWindow dialog(this);

	dialog.exec();
}

void SimulationMainWindow::on_startButton_clicked()
{
	/*Blocage du bouton paramètre et débloquage
	du bouton stop et pause.*/
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);


	mTimer.start(30);
}

void SimulationMainWindow::on_pauseButton_clicked()
{
	/*Déblocage des boutons reprendre et par étape.*/
	ui.stepButton->setEnabled(true);
	ui.resumeButton->setEnabled(true);

	mTimer.stop();
}

void SimulationMainWindow::on_resumButton_clicked()
{
	/*Blocage du bouton par étape*/
	ui.stepButton->setEnabled(false);

	mTimer.start(30);
}

void SimulationMainWindow::on_stepButton_clicked()
{

}

void SimulationMainWindow::on_stopButton_clicked()
{
	mGraphicsScene.clear();

	mTimer.stop();
}