/*#include "stdafx.h"

#include "constantes.h"
#include "ClassesSimulateur/Coordonne.h"
#include "ImplementantionFonctionsGenerales.h"
#include <iostream>

int main(void)
{
	//test du retour de la valeur de la distance

	//DistanceEntre2Points(Coordonne(7,7), pt2);

	//Test de atan2
	VitesseVersAngle(-7, -7);

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
