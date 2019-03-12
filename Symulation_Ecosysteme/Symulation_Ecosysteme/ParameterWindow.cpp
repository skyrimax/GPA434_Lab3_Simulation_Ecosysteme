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
	u8R"---(Choisisez le prédateur et l'herbivore désiré parmis les choix proposés dans la liste déroulante. Entrez le nombre de chaque esèce avec laquelle démarrer la simulation.

Dans la zone "Option de simulation", ce sont des ajouts possibles 
à la simulation, tel que :
	-Présence de charognards permettra la présence de ceux-ci afin
	de modifier la simulation, car ceux-ci vont manger les proies 
	qu'ils n'ont pas tués eux-même. Une fois la case coché, choisisez
	l'expèce désiré et le nombre de spéciment à incorporer dans la 
	simulation au départ.
	-Ajout de saison permettra un changement de climat, comportement
	 animalier au fil du temps.
	-Ajout de maladies ajoutera la possiblité de maladies, virus et
	 contamination. Cela se fera soit par des plantes toxiques, viande
	 en décomposition ou autres.

Une fois vos choix finaliser, appuyez sur le bouton "Done" pour fermer
 la fenêtre et revenir à la fenêtre de simulation.)---" };

	//Afficher le message

	QMessageBox::about(this, u8R"(Aide aux paramètres)", aide);
}


