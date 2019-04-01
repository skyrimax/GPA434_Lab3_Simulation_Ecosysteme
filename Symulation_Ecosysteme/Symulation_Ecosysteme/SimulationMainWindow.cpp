#include "stdafx.h"
#include "SimulationMainWindow.h"
#include "ParameterWindow.h"

SimulationMainWindow::SimulationMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*D�sactivation des boutons de la simulation afin
	que l'utilisateur rentre ses param�tres avant*/
	ui.pauseButton->setEnabled(false);
	ui.resumeButton->setEnabled(false);
	ui.stepButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	/*Connection entre le mTimer et la fonction qui va simuler l'�cosyst�me,
	� chaque 30 millisecondes, un signal sera "envoy�" vers la fonction
	afin de mettre � jour les positions et les �tats.*/
	connect(&mTimer, &QTimer::timeout, environnement, &Environnement::simulation);
	}

void SimulationMainWindow::showAPropos()
{
	//Cr�er le message
	QString aboutProgramm{ \
	u8R"---(EcoSimulated est un logiciel de simulation d'un �cosyst�me incluant
 les plantes, lapins, chevreuils et loups.

Ce programme a �t� r�alis� par :
	- Fr�d�ric Grondines
	- Guillaume Faucher
	- Mathieu Labelle
	- Maxime Royal
	- Mika�l Valton Charette

Dans le cadre du cours :
	- GPA434 - Ing�nierie des syst�mes orient�s-objet
	- Laboratoire 3

Version 1.0)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(� propos)", aboutProgramm);
}

void SimulationMainWindow::on_parameterButton_clicked()
{
	ParameterWindow dialog(this);

	dialog.exec();
}

void SimulationMainWindow::on_startButton_clicked()
{
	/*Blocage du bouton param�tre et d�bloquage
	du bouton stop et pause.*/
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);


	mTimer.start(30);
}

void SimulationMainWindow::on_pauseButton_clicked()
{
	/*D�blocage des boutons reprendre et par �tape.*/
	ui.stepButton->setEnabled(true);
	ui.resumeButton->setEnabled(true);

	mTimer.stop();
}

void SimulationMainWindow::on_resumButton_clicked()
{
	/*Blocage du bouton par �tape*/
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