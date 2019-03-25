#pragma once

#include "stdafx.h"
#include "ClassesSimulateur/Coordonne.h"

//Definition des types employes pour le programme et fonctions generales 
//
//

//Fonction qui retourne la distance entre 2 points dans l environnement
double distanceEntre2Points(Coordonne pt1,Coordonne pt2);

//Fonction qui qui retourne l angle d orientation a partir de l axe des x avec vecteur vitesse
double vitesseVersAngle(double vx,double vy);

//Fonction qui retourne le point cartesien de croisement de la trajectoire dun animal avec la frontiere  
//Croisement entre 2 lignes (trajectoire, frontiere)
