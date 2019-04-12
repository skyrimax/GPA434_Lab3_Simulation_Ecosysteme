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

	/*1ere méthode envoit un signal à la fonction advance de QGrpahicScene*/
	connect(&mTimer, &QTimer::timeout, &mGraphicsScene, &QGraphicsScene::advance);

	/*Connection entre le mTimer et la fonction qui va simuler l'écosystème,
	à chaque 30 millisecondes, un signal sera "envoyé" vers la fonction
	afin de mettre à jour les positions et les états.*/
	//connect(&mTimer, &QTimer::timeout, environnement, &Environnement::simulation);

	}

/*Fonction À Propos pour expliquer le programme*/
void SimulationMainWindow::showAPropos()
{
	//Créer le message
	QString aboutProgramm{ \
	u8R"---(EcoSimulated est un logiciel de simulation d'un écosystème incluant les plantes, lapins, chevreuils et loups. Dans cette simulation, les loups vont chercher à se nourrir en chassant les chevreuils, ces derniers vont tenter de s'échapper des loups mais devront également trouver de la nourriture, les plantes, pour survivre. Les plantes ont des fruits qui vont nourrir les chevreuils, les plantes vont donc perdre des fruits, mais  d'autres fruits repousseront avec le temps. Il y a aussi un système de reproduction propre à chaque espèce, afin d'assurer leur survie.

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

/*Ouverture des paramètre lors de l'activation du bouton*/
void SimulationMainWindow::on_parameterButton_clicked()
{
	ParameterWindow dialog(this);

	dialog.exec();
}

/*Début de la simulation en appuyant sur start*/
void SimulationMainWindow::on_startButton_clicked()
{
	//Création de la grid du terrain
	Grid *m_grid;

	/*Blocage du bouton paramètre et débloquage
	du bouton stop et pause.*/
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);

	// Vide la scène pour démarrer une nouvelle démo
	mGraphicsScene.clear();

	//Ajout du terrain à la scène
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
	/*Déblocage des boutons reprendre et par étape.*/
	ui.stepButton->setEnabled(true);
	ui.resumeButton->setEnabled(true);

	mTimer.stop();
}

/*Continue la simulation là où elle était*/
void SimulationMainWindow::on_resumButton_clicked()
{
	/*Blocage du bouton par étape*/
	ui.stepButton->setEnabled(false);

	mTimer.start(30);
}

/*Envoie un singal à simulation à chaque fois qu'on pèse
sur le bouton Par Étape*/
void SimulationMainWindow::on_stepButton_clicked()
{
	/*1ere méthode avec la fonction advance de QGraphicsScene*/
	//mGraphicsScene.advance();

	/*2ene méthode utilise directement la fonction simulatiom*/
	//environnement->simulation();
}

/*Bouton qui arrête la simulation en arrêtant le timer
et en effacant le GraphicView*/
void SimulationMainWindow::on_stopButton_clicked()
{
	mGraphicsScene.clear();

	mTimer.stop();
}