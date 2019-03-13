#include "stdafx.h"
#include "ParameterWindow.h"

ParameterWindow::ParameterWindow(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	
;
}

ParameterWindow::~ParameterWindow()
{
}

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


