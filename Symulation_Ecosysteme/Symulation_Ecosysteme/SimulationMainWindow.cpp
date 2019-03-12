#include "stdafx.h"
#include "SimulationMainWindow.h"
#include "ParameterWindow.h"

SimulationMainWindow::SimulationMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void SimulationMainWindow::showAPropos()
{
	//Cr�er le message
	QString aboutProgramm{ \
	u8R"---(EcoSimulated est un logiciel de simulation d'un �cosyst�me incluant
 les plantes, herbivores et carnivore.

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
}

void SimulationMainWindow::on_parameterButton_clicked()
{
	ParameterWindow dialog(this);

	dialog.exec();
}
