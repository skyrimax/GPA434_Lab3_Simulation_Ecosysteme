#include "stdafx.h"
#include "ParameterWindow.h"



ParameterWindow::ParameterWindow(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	
	//D�sactivation des mods qui seront ajout� ult�rieurement si on a le temps
	viruscheckBox->setEnabled(false);
	seasoncheckBox->setEnabled(false);
}

ParameterWindow::~ParameterWindow()
{
}

/*Affichage d'un message d'aide pour guider dans 
la s�lection des param�tres*/
void ParameterWindow::showAide()
{
	//Cr�er le message
	QString aide{ \
	u8R"---(Tout d'abord, d�terminez le nombre de d�part pour les lapins, chevreuils et loups.
	La quantit� maximale est fix�e � 100 pour chaques esp�ces. Ensuite, d�terminez le nombre
	 de hordes de chevreuils d�sir�es ainsi que le nombre de meutes de loup. Le nombre maximale
	de regroupement d'animaux est fix� � 10 pour chacune des esp�ces.)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(Aide aux param�tres)", aide);
}

/*Retourne la quantit� de lapins pour d�buter la simulation*/
int ParameterWindow::getQteLapin()
{
	return qteLapins->value();
}

/*Retourne la quantit� de chevreuils pour d�buter la simulation*/
int ParameterWindow::getQteChevreuil()
{

	return qteChevreuils->value();
}

/*Retourne la quantit� de loups pour d�buter la simulation*/
int ParameterWindow::getQteLoup()
{
	return qteLoups->value();
}

/*Retourne la quantit� de harde de chevreuil pour d�buter la simulation*/
int ParameterWindow::getQteHarde()
{
	return qteHardes->value();
}

/*Retourne la quantit� de meute de loup pour d�buter la simulation*/
int ParameterWindow::getQteMeute()
{
	return qteMeutes->value();
}

/*Renvoie si la case pour le mode saison a �t� coch�*/
bool ParameterWindow::isSeasonCheck()
{
	return seasoncheckBox->isChecked();
}

/*Renvoie si la case pour le mode virus a �t� coch�*/
bool ParameterWindow::isVirusCheck()
{
	return viruscheckBox->isChecked();
}

