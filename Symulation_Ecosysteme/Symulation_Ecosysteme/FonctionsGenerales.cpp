
#define _USE_MATH_DEFINES

#include "stdafx.h"
#include "FonctionsGenerales.h"
#include "ClassesSimulateur/Coordonne.h"
#include <cmath>
#include <iostream>


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
