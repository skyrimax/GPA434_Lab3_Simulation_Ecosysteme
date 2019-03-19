/**
 * Project Untitled
 */


#ifndef _VELOCITE_H
#define _VELOCITE_H

#include "FonctionsGenerales.h"

class Orientation {
public: 

	// Accesseur du vecteur de base
	double getVX();
	double getVY();

	// Accesseur du vecteur unitaire
	double getUnitX();
	double getUnitY();

	// Mutateur du vecteur de base
	void setVX(double vX);
	void setVY(double vY);

	// Fonction membre permettant de déplacer le vecteur de base
	void moveVX(double deltaVX);
	void moveVY(double deltaVY);

private: 

	// Fonction menbre recalculant le vecreur unitaire
	void unitV();

	// Composantes du vecteur de base
    double m_vX;
    double m_vY;

	// Composantes du vecteur unitaire
	double m_unitX;
	double m_unitY;

	// Direction du vecteur
	double m_direction
};

#endif //_VELOCITE_H