#include "stdafx.h"
#include "SimulationMainWindow.h"
#include "ParameterWindow.h"
#include <QRandomGenerator>


SimulationMainWindow::SimulationMainWindow(QWidget *parent)
	: QMainWindow(parent), mQteChevreuils{ 1 }, mQteLapins{ 1 }, mQteLoups{ 1 }
	, mQteMeuteLoups{ 1 }, mQteHardeChevreuil{ 1 }
{
	ui.setupUi(this);

	/*Désactivation des boutons de la simulation afin
	que l'utilisateur rentre ses paramètres avant*/
	ui.pauseButton->setEnabled(false);
	ui.resumeButton->setEnabled(false);
	ui.stepButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	/*1ere méthode envoit un signal à la fonction advance de QGrpahicScene*/
	//connect(&mTimer, &QTimer::timeout, &mGraphicsScene, &QGraphicsScene::advance);

	//connect(&mTimer, &QTimer::timeout, this, &SimulationMainWindow::simulation);
}



void SimulationMainWindow::addTerrain(Grid *m_grid, Environnement *environnement)
{
	for (int i = 0; i < LARGEUR_GRILLE; i++)
	{
		for (int j = 0; j < HAUTEUR_GRILLE; j++)
		{
			mGraphicsScene.addItem(new Terrain(
				m_grid,
				i,
				j,
				m_grid->getTerrain(i, j)->getType()));

			if ((m_grid->getTerrain(i, j)->getType() != Terrain::TypeTerrain::Eau) &&
				(m_grid->getTerrain(i, j)->getType() != Terrain::TypeTerrain::Terre) &&
				(m_grid->getTerrain(i, j)->getType() != Terrain::TypeTerrain::Gazon) &&
				(m_grid->getTerrain(i, j)->getType() != Terrain::TypeTerrain::Frontiere))
			{
				Plante *plante = new Plante(
					environnement, /*Ajouter non de plante ici*/ "Arbre",
					/*Ajouter hp ici*/ 1, /*Ajouter energy*/1, /*Ajouter age adulte*/ 10, /*Ajouter age max*/100,
					randomCoordonne().getX(), randomCoordonne().getY(), /*Ajouter temps reproduction*/ 300);

				environnement->addPlante(plante);
				mGraphicsScene.addItem(plante);
			}
		}
	}
}


void SimulationMainWindow::addHerbivore(Environnement *environnement)
{
	for (int i = 0; i < mQteChevreuils; i++)
	{
		Herbivore *Chevreuil = new Herbivore(
			environnement,//Environnement
			std::string("Chevreuil"),//Espèce
			100,//hp
			100,//energy
			10,//ageadulte
			20,//agemax
			randomCoordonne().getX(),//x
			randomCoordonne().getY(),//y
			2,//vitesse
			4,//sprint
			randomSex(),//sex
			0,//nbProgenituremin
			4,//nbprogenituremax
			nullptr,//mere
			nullptr,//meute
			50,//timermort
			10,//tempsgestation
			5,//tempsreproduction
			std::list<std::string> {"Plante"});
		Chevreuil->setAge(10);


		environnement->addHerbivore(Chevreuil);

		mGraphicsScene.addItem(Chevreuil);
	}
	for (int i = 0; i < mQteLapins; i++)
	{
		Herbivore *Lapin = new Herbivore(
			environnement,//Environnement
			std::string("Lapin"),//Espèce
			100,//hp
			100,//energy
			10,//ageadulte
			20,//agemax
			randomCoordonne().getX(),//x
			randomCoordonne().getY(),//y
			2,//vitesse
			4,//sprint
			randomSex(),//sex
			0,//nbProgenituremin
			4,//nbprogenituremax
			nullptr,//mere
			nullptr,//meute
			50,//timermort
			10,//tempsgestation
			5,//tempsreproduction
			std::list<std::string> {"Plante"});
		Lapin->setAge(10);
		environnement->addHerbivore(Lapin);

		mGraphicsScene.addItem(Lapin);
	}
}


void SimulationMainWindow::addCarnivore(Environnement *environnement)
{
	for (int i = 0; i < mQteLoups; i++)
	{
		Carnivore *Loup = new Carnivore(
			environnement,//Environnement
			std::string("Loup"),//Espèce
			100,//hp
			100,//energy
			10,//ageadulte
			20,//agemax
			randomCoordonne().getX(),//x
			randomCoordonne().getY(),//y
			2,//vitesse
			4,//sprint
			randomSex(),//sex
			0,//nbProgenituremin
			4,//nbprogenituremax
			nullptr,//mere
			nullptr,//meute
			50,//timermort
			10,//tempsgestation
			5,//tempsreproduction
			std::list<std::string> {"Chevreuil", "Lapin"},
			false);
		Loup->setAge(10);
		environnement->addCarnivore(Loup);//Ajout à l'environnement
		mGraphicsScene.addItem(Loup);//Ajout à la scène
	}
}


void SimulationMainWindow::simulation()
{
	environnement->simulation();
}


Animal::Sex SimulationMainWindow::randomSex()
{
	return Animal::Sex(QRandomGenerator::global()->bounded(0,2));
}


Coordonne SimulationMainWindow::randomCoordonne()
{
	return Coordonne(QRandomGenerator::global()->bounded(0, LARGEUR_GRILLE-1), QRandomGenerator::global()->bounded(0, HAUTEUR_GRILLE-1));
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

Version 0.1)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(À propos)", aboutProgramm);
}

/*Ouverture des paramètre lors de l'activation du bouton*/
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

/*Début de la simulation en appuyant sur start*/
void SimulationMainWindow::on_startButton_clicked()
{

	/*Blocage du bouton paramètre et débloquage
	du bouton stop et pause.*/
	ui.parameterButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	ui.pauseButton->setEnabled(true);
	ui.startButton->setEnabled(false);

	environnement = new Environnement(); //Génération d'un envirronement

	//addTerrain(environnement->getGrille(), environnement);//Ajout du terrain
	addHerbivore(environnement);//Ajout des herbivores
	addCarnivore(environnement);//Ajout des carnivores

	ui.graphicsView->setScene(&mGraphicsScene);

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

	delete environnement;

	environnement = nullptr;

	ui.parameterButton->setEnabled(true);
	ui.startButton->setEnabled(true);
}