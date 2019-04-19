#include "stdafx.h"
#include "SimulationMainWindow.h"
#include "ParameterWindow.h"
#include <QRandomGenerator>


SimulationMainWindow::SimulationMainWindow(QWidget *parent)
	: QMainWindow(parent), mQteChevreuils{ 1 }, mQteLapins{ 1 }, mQteLoups{ 1 },
	mQteMeuteLoups{ 0 }, mQteHardeChevreuil{ 0 }, simulationEnCours{false}
{
	ui.setupUi(this);

	/*D�sactivation des boutons de la simulation afin
	que l'utilisateur rentre ses param�tres avant*/
	ui.pauseButton->setEnabled(false);
	ui.resumeButton->setEnabled(false);
	ui.stepButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	/*1ere m�thode envoit un signal � la fonction advance de QGrpahicScene*/
	//connect(&mTimer, &QTimer::timeout, &mGraphicsScene, &QGraphicsScene::advance);

	connect(&mTimer, &QTimer::timeout, this, &SimulationMainWindow::simulation);
}

/*Fonction qui va ajout� le type de terrain � chaque case (500 X 500) 
dans le QGraphicsView*/
void SimulationMainWindow::addTerrain(Grid *m_grid, Environnement *environnement)
{
	for (int i = 0; i < LARGEUR_GRILLE; i++)
	{
		for (int j = 0; j < HAUTEUR_GRILLE; j++)
		{
			mGraphicsScene.addItem(environnement->getTerrain(i, j));
		}
	}
}


void SimulationMainWindow::addVivants(Environnement *environnement)
{
	//Les 3 boucles For sont temporaire
	for (int i = 0; i < mQteChevreuils; i++)//Ajout des chevreuils
	{
		Herbivore *Chevreuil = new Herbivore(
			environnement,//Environnement
			std::string("Chevreuil"),//Esp�ce
			100,//hp
			3000,//energy
			600,//ageadulte
			3600,//agemax
			randomCoordonne().getX(),//x
			randomCoordonne().getY(),//y
			2,//vitesse
			4,//sprint
			randomSex(),//sex
			0,//nbProgenituremin
			4,//nbprogenituremax
			nullptr,//mere
			nullptr,//meute
			300,//timermort
			450,//tempsgestation
			900,//tempsreproduction
			std::list<std::string> {"Plante"});
		Chevreuil->setAge(600);
		//Chevreuil->setEnergy(1500);
		environnement->addHerbivore(Chevreuil);

	}
	for (int i = 0; i < mQteLapins; i++)//Ajout des lapins
	{
		Herbivore *Lapin = new Herbivore(
			environnement,//Environnement
			std::string("Lapin"),//Esp�ce
			100,//hp
			3000,//energy
			600,//ageadulte
			3600,//agemax
			randomCoordonne().getX(),//x
			randomCoordonne().getY(),//y
			2,//vitesse
			4,//sprint
			randomSex(),//sex
			0,//nbProgenituremin
			4,//nbprogenituremax
			nullptr,//mere
			nullptr,//meute
			300,//timermort
			450,//tempsgestation
			900,//tempsreproduction
			std::list<std::string> {"Plante"});
		Lapin->setAge(600);
		//Lapin->setEnergy(1500);
		environnement->addHerbivore(Lapin);
	}
	for (int i = 0; i < mQteLoups; i++)//Ajout des loups
	{
		Carnivore *Loup = new Carnivore(
			environnement,//Environnement
			std::string("Loup"),//Esp�ce
			100,//hp
			3000,//energy
			600,//ageadulte
			3600,//agemax
			randomCoordonne().getX(),//x
			randomCoordonne().getY(),//y
			2,//vitesse
			5,//sprint
			randomSex(),//sex
			0,//nbProgenituremin
			4,//nbprogenituremax
			nullptr,//mere
			nullptr,//meute
			300,//timermort
			450,//tempsgestation
			900,//tempsreproduction
			std::list<std::string> {"Chevreuil", "Lapin"},
			false);

		Loup->setAge(600);
		//Loup->setEnergy(1500);
		environnement->addCarnivore(Loup);//Ajout � l'environnement
	}

}

void SimulationMainWindow::simulation()
{
	mTimer.stop();

	if (!simulationEnCours) {
		simulationEnCours = true;

		mTimer.start(30);

		environnement->simulation();

		simulationEnCours = false;
	}
}


Animal::Sex SimulationMainWindow::randomSex()
{
	return Animal::Sex(QRandomGenerator::global()->bounded(0,2));
}


Coordonne SimulationMainWindow::randomCoordonne()
{
	return Coordonne(QRandomGenerator::global()->bounded(0, LARGEUR_GRILLE-1), QRandomGenerator::global()->bounded(0, HAUTEUR_GRILLE-1));
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

Version 0.1)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(� propos)", aboutProgramm);
}

/*Ouverture des param�tre lors de l'activation du bouton*/
void SimulationMainWindow::on_parameterButton_clicked()
{
	ParameterWindow dialog(this);

	if (dialog.exec())
	{
		mQteChevreuils = dialog.qteChevreuils->value();
		mQteLapins = dialog.qteLapins->value();
		mQteLoups = dialog.qteLoups->value();
		mQteMeuteLoups = dialog.qteMeutes->value();
		mQteHardeChevreuil = dialog.qteHardes->value();
	}
}

/*D�but de la simulation en appuyant sur start*/
void SimulationMainWindow::on_startButton_clicked()
{

	/*Blocage du bouton param�tre et d�bloquage
	du bouton stop et pause.*/
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);
	ui.startButton->setEnabled(false);

	environnement = new Environnement(); //G�n�ration d'un envirronement

	environnement->setSceneRect(0, 0, LARGEUR_GRILLE, HAUTEUR_GRILLE);

	addVivants(environnement);

	ui.graphicsView->setFixedSize(LARGEUR_GRILLE, HAUTEUR_GRILLE);
	ui.graphicsView->setScene(environnement);//Ajout de la sc�ne dans le QGraphicsView

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
	/*2ene m�thode utilise directement la fonction simulatiom*/
	environnement->simulation();
}

/*Bouton qui arr�te la simulation en arr�tant le timer
et en effacant le GraphicView*/
void SimulationMainWindow::on_stopButton_clicked()
{
	mTimer.stop();

	if (environnement != nullptr) {
		delete environnement;
	}

	environnement = nullptr;

	ui.parameterButton->setEnabled(true);
	ui.startButton->setEnabled(true);
}