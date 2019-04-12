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

	/*1ere m�thode envoit un signal � la fonction advance de QGrpahicScene*/
	connect(&mTimer, &QTimer::timeout, &mGraphicsScene, &QGraphicsScene::advance);

	/*Connection entre le mTimer et la fonction qui va simuler l'�cosyst�me,
	� chaque 30 millisecondes, un signal sera "envoy�" vers la fonction
	afin de mettre � jour les positions et les �tats.*/
	//connect(&mTimer, &QTimer::timeout, environnement, &Environnement::simulation);

	}

/*Fonction � Propos pour expliquer le programme*/
void SimulationMainWindow::showAPropos()
{
	//Cr�er le message
	QString aboutProgramm{ \
	u8R"---(EcoSimulated est un logiciel de simulation d'un �cosyst�me incluant les plantes, lapins, chevreuils et loups. Dans cette simulation, les loups vont chercher � se nourrir en chassant les chevreuils, ces derniers vont tenter de s'�chapper des loups mais devront �galement trouver de la nourriture, les plantes, pour survivre. Les plantes ont des fruits qui vont nourrir les chevreuils, les plantes vont donc perdre des fruits, mais  d'autres fruits repousseront avec le temps. Il y a aussi un syst�me de reproduction propre � chaque esp�ce, afin d'assurer leur survie.

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

/*Ouverture des param�tre lors de l'activation du bouton*/
void SimulationMainWindow::on_parameterButton_clicked()
{
	ParameterWindow dialog(this);

	dialog.exec();
}

/*D�but de la simulation en appuyant sur start*/
void SimulationMainWindow::on_startButton_clicked()
{
	//Cr�ation de la grid du terrain
	Grid *m_grid;

	/*Blocage du bouton param�tre et d�bloquage
	du bouton stop et pause.*/
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);

	// Vide la sc�ne pour d�marrer une nouvelle d�mo
	mGraphicsScene.clear();

	//Ajout du terrain � la sc�ne
	for (int i = 0; i < LARGEUR_GRILLE; i++) {
		for (int j = 0; j < HAUTEUR_GRILLE; j++) {
			mGraphicsScene.addItem(new Terrain(
				m_grid,
				i,
				j,
				m_grid->getTerrain(i,j)->getType()));
		}
	}



	mTimer.start(30);
}

/*Met la simulation en pause en arretant le timer*/
void SimulationMainWindow::on_pauseButton_clicked()
{
	/*D�blocage des boutons reprendre et par �tape.*/
	ui.stepButton->setEnabled(true);
	ui.resumeButton->setEnabled(true);

	mTimer.stop();
}

/*Continue la simulation l� o� elle �tait*/
void SimulationMainWindow::on_resumButton_clicked()
{
	/*Blocage du bouton par �tape*/
	ui.stepButton->setEnabled(false);

	mTimer.start(30);
}

/*Envoie un singal � simulation � chaque fois qu'on p�se
sur le bouton Par �tape*/
void SimulationMainWindow::on_stepButton_clicked()
{
	/*1ere m�thode avec la fonction advance de QGraphicsScene*/
	//mGraphicsScene.advance();

	/*2ene m�thode utilise directement la fonction simulatiom*/
	//environnement->simulation();
}

/*Bouton qui arr�te la simulation en arr�tant le timer
et en effacant le GraphicView*/
void SimulationMainWindow::on_stopButton_clicked()
{
	mGraphicsScene.clear();

	mTimer.stop();
}