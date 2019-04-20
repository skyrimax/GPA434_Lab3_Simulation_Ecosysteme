
#define _USE_MATH_DEFINES

#include "stdafx.h"
#include "FonctionsGenerales.h"
#include "ClassesSimulateur/Coordonne.h"
#include <cmath>
#include <iostream>
#include "constantes.h"
#include <vector>


double distanceEntre2Points(Coordonne pt1, Coordonne pt2)
{
	double distance;

	//distance entre 2 coordonnees
	distance = sqrt(pow((pt2.getX() - pt1.getX()), 2)+pow((pt2.getY() - pt1.getY()), 2));

	return distance;
}

double vitesseVersAngle(double vx, double vy)
{
	double angle;

	//Calcul de l angle cree par le vecteur vitesse
	angle = atan2(vy, vx) * (180 / M_PI);

	//Coversion de l angle desire avec vitesses negatives
	if(angle < 0)
	{
		angle = angle + 360;
	}
	return angle;
}

Coordonne croisementEntre2Lignes(Coordonne depart, Coordonne destination)
{		
	Coordonne futureDestination;

	Coordonne maxWorldLimit= Coordonne(LARGEUR_GRILLE, HAUTEUR_GRILLE);
	
	Coordonne minWorldLimit = Coordonne(0, 0);

	//Si la destination est depasser la limite du coin superieur gauche (x<0, y<0) de la grille de l'environnement de la simulation 
	if (destination.getX() < minWorldLimit.getX() && destination.getY() < minWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite
		double frontiereX = 0;
		double frontiereY = 0;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleX = abs((frontiereX - depart.getX()) / deltaX);
		double scaleY = abs((frontiereY - depart.getY()) / deltaY);

		if (scaleX < scaleY) {
			scaleY = scaleX;
		}
		else {
			scaleX = scaleY;
		}

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX, depart.getY()+deltaY*scaleY);
		
		return futureDestination;
	}

	//Si la destination est depasser la limite gauche (x<0, 0<y<500) de la grille de l'environnement de la simulation 
	else if (destination.getX() < minWorldLimit.getX() && destination.getY() > minWorldLimit.getY() && destination.getY() < maxWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite 
		double frontiereX = 0;
		double frontiereY = 500;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleX = abs((frontiereX - depart.getX()) / deltaX );
		double scaleY = scaleX;

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX, depart.getY()+deltaY*scaleY);

		return futureDestination;
	}

	//Si la destination est depasser la limite du coin inferieur gauche (x<0, y>500) de la grille de l'environnement de la simulation 
	else if (destination.getX() < minWorldLimit.getX() && destination.getY() > maxWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite
		double frontiereX = 500;
		double frontiereY = 500;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleY = abs((frontiereY - depart.getY()) / deltaY);
		double scaleX = abs((frontiereX - depart.getX()) / deltaX);

		if (scaleX < scaleY) {
			scaleY = scaleX;
		}
		else {
			scaleX = scaleY;
		}

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX, depart.getY()+deltaY*scaleY);

		return futureDestination;
	}

	//Si la destination est depasser la limite inferieure (plus de 0<x<500, y>500) de la grille de l'environnement de la simulation 
	else if (destination.getX() > minWorldLimit.getX() && destination.getX() < maxWorldLimit.getX() && destination.getY() > maxWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite 
		double frontiereX = 500;
		double frontiereY = 500;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleY = abs((frontiereY - depart.getY()) / deltaY);
		double scaleX = scaleY;

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX , depart.getY()+deltaY*scaleY);

		return  futureDestination;
	}

	//Si la destination est depasser la limite du coin inferieur droit (x>500, y>500) de la grille de l'environnement de la simulation 
	else if (destination.getX() >= maxWorldLimit.getX() && destination.getY() >= maxWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite 
		double frontiereX = 500;
		double frontiereY = 500;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleX = abs((frontiereX - depart.getX()) / deltaX);
		double scaleY = abs((frontiereY - depart.getY()) / deltaY);

		if (scaleX < scaleY) {
			scaleY = scaleX;
		}
		else {
			scaleX = scaleY;
		}

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX, depart.getY()+deltaY*scaleY);

		return futureDestination;
	}

	//Si la destination est depasser la limite droite (x>500, 0<y<500)de la grille de l'environnement de la simulation
	else if (destination.getX() > maxWorldLimit.getX() && destination.getY() > minWorldLimit.getY() && destination.getY() < maxWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite 
		double frontiereX = 500;
		double frontiereY = 500;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleX = abs((frontiereX - depart.getX()) / deltaX );
		double scaleY = scaleX;

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX, depart.getY()+deltaY*scaleY);

		return futureDestination;
	}

	//Si la destination est depasser la limite du coin superieur droit (x>500, y<0) de la grille de l'environnement de la simulation
	else if (destination.getX() > maxWorldLimit.getX() && destination.getY() < minWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite 
		double frontiereX = 500;
		double frontiereY = 0;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleX = abs((frontiereX - depart.getX()) / deltaX);
		double scaleY = abs((frontiereY - depart.getY()) / deltaY);

		if (scaleX < scaleY) {
			scaleY = scaleX;
		}
		else {
			scaleX = scaleY;
		}

		futureDestination = Coordonne(depart.getX() + deltaX * scaleX, depart.getY() + deltaY * scaleY);

		return futureDestination;
	}

	//Si la destination est depasser la limite superieure ( 0<x<500 , y<0) de la grille de l'environnement de la simulation
	else if (destination.getX() < maxWorldLimit.getX() && destination.getY() < minWorldLimit.getY())
	{
		//etablissement des parametres our le calcul de la nouvelle coordonne limite 
		double frontiereX = 500;
		double frontiereY = 0;
		double deltaX = destination.getX() - depart.getX();
		double deltaY = destination.getY() - depart.getY();

		//Calcul du facteur d echelle
		double scaleY = abs((frontiereY - depart.getY()) / deltaY);
		double scaleX = scaleY;

		futureDestination = Coordonne(depart.getX()+deltaX*scaleX, depart.getY()+deltaY*scaleY);

		return futureDestination;
	}

	//Si la destination est à l'intérieur de la grille de l'environnement de la simulation
	else
	
	futureDestination = Coordonne(-1,-1);

	return futureDestination;
}

