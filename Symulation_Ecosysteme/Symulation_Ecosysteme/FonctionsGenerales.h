#pragma once

#define _USE_MATH_DEFINES

#include "stdafx.h"
#include "ClassesSimulateur/Coordonne.h"


//Fonction qui retourne la distance entre 2 points dans l environnement
double distanceEntre2Points(Coordonne pt1,Coordonne pt2);

//Fonction qui qui retourne l angle d orientation a partir de l axe des x avec vecteur vitesse
double vitesseVersAngle(double vx,double vy);

//Fonction qui retourne le point cartesien de croisement de la trajectoire dun animal avec la frontiere  
Coordonne croisementEntre2Lignes(Coordonne depart, Coordonne destination);
