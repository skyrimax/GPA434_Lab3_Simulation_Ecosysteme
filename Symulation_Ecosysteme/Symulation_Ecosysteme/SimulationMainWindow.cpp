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
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);

	environnement = new Environnement();
}

void SimulationMainWindow::on_pauseButton_clicked()
{
	ui.stepButton->setEnabled(true);
	ui.resumeButton->setEnabled(true);
}

void SimulationMainWindow::on_resumButton_clicked()
{
	ui.stepButton->setEnabled(false);
}

void SimulationMainWindow::on_stepButton_clicked()
{

}

void SimulationMainWindow::on_stopButton_clicked()
{
	mGraphicsScene.clear();
}