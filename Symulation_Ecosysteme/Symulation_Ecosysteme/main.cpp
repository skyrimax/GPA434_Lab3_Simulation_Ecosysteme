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
}
