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
	u8R"---(Choisisez le pr�dateur et l'herbivore d�sir� parmis les choix propos�s dans la liste d�roulante. Entrez le nombre de chaque es�ce avec laquelle d�marrer la simulation.

Dans la zone "Option de simulation", ce sont des ajouts possibles 
� la simulation, tel que :
	-Pr�sence de charognards permettra la pr�sence de ceux-ci afin
	de modifier la simulation, car ceux-ci vont manger les proies 
	qu'ils n'ont pas tu�s eux-m�me. Une fois la case coch�, choisisez
	l'exp�ce d�sir� et le nombre de sp�ciment � incorporer dans la 
	simulation au d�part.
	-Ajout de saison permettra un changement de climat, comportement
	 animalier au fil du temps.
	-Ajout de maladies ajoutera la possiblit� de maladies, virus et
	 contamination. Cela se fera soit par des plantes toxiques, viande
	 en d�composition ou autres.

Une fois vos choix finaliser, appuyez sur le bouton "Done" pour fermer
 la fen�tre et revenir � la fen�tre de simulation.)---" };

	//Afficher le message

	QMessageBox::about(this, u8R"(Aide aux param�tres)", aide);
}


