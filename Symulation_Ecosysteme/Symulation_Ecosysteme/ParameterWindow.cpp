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
	//Cr�er le message
	QString aide{ \
	u8R"---(Tout d'abord, d�terminez le nombre de d�part pour les lapins, chevreuils et loups.
	La quantit� maximale est fix�e � 100 pour chaques esp�ces. Ensuite, d�terminez le nombre
	 de hordes de chevreuils d�sir�es ainsi que le nombre de meutes de loup. Le nombre maximale
	de regroupement d'animaux est fix� � 10 pour chacune des esp�ces.)---" };

	//Afficher le message
	QMessageBox::about(this, u8R"(Aide aux param�tres)", aide);
}


