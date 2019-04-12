/*#include "stdafx.h"

#include "constantes.h"
#include "ClassesSimulateur/Coordonne.h"
#include "FonctionsGenerales.h"
#include <iostream>

int main(void)
{
	//test du retour de la valeur de la distance
	distanceEntre2Points(Coordonne(7,7), Coordonne(50, 50));

	//Test de atan2
	vitesseVersAngle(-7, -7);

	//Test de la foction qui recalcule les limites du monde de simulation
	croisementEntre2Lignes(Coordonne(250,250), Coordonne(300,300));

	return EXIT_SUCCESS;
}*/

/*Ajout par Fred, q
uelqu'un avait effacé le main, qui contient les lignes de code
pour faire fonctioner QT.
*****NE PLUS EFFACER********/
#include "stdafx.h"
#include "SimulationMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimulationMainWindow w;
	w.show();
	return a.exec();
}
