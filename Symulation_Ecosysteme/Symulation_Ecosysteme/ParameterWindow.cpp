#include "stdafx.h"
#include "ParameterWindow.h"



ParameterWindow::ParameterWindow(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	
	//Désactivation des mods qui seront ajouté ultérieurement si on a le temps
	viruscheckBox->setEnabled(false);
	seasoncheckBox->setEnabled(false);
}

ParameterWindow::~ParameterWindow()
{
}

/*Affichage d'un message d'aide pour guider dans 
la sélection des paramètres*/
void ParameterWindow::showAide()
{
	//Créer le message
	QString aide{ \
	u8R"---(Tout d'abord, déterminez le nombre de départ pour les lapins, chevreuils et loups.
	La quantité maximale est fixée à 100 pour chaques espèces. Ensuite, déterminez le nombre
	 de hordes de chevreuils désirées ainsi que le nombre de meutes de loup. Le nombre maximale
	de regroupement d'animaux est fixé à 10 pour chacune des espèces.)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(Aide aux paramètres)", aide);
}

/*Retourne la quantité de lapins pour débuter la simulation*/
int ParameterWindow::getQteLapin()
{
	return qteLapins->value();
}

/*Retourne la quantité de chevreuils pour débuter la simulation*/
int ParameterWindow::getQteChevreuil()
{

	return qteChevreuils->value();
}

/*Retourne la quantité de loups pour débuter la simulation*/
int ParameterWindow::getQteLoup()
{
	return qteLoups->value();
}

/*Retourne la quantité de harde de chevreuil pour débuter la simulation*/
int ParameterWindow::getQteHarde()
{
	return qteHardes->value();
}

/*Retourne la quantité de meute de loup pour débuter la simulation*/
int ParameterWindow::getQteMeute()
{
	return qteMeutes->value();
}

/*Renvoie si la case pour le mode saison a été coché*/
bool ParameterWindow::isSeasonCheck()
{
	return seasoncheckBox->isChecked();
}

/*Renvoie si la case pour le mode virus a été coché*/
bool ParameterWindow::isVirusCheck()
{
	return viruscheckBox->isChecked();
}

