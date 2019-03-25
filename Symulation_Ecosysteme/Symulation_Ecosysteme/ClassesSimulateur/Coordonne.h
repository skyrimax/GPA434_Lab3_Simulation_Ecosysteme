/**
 * Project Untitled
 */


#ifndef _COORDONNE_H
#define _COORDONNE_H

class Coordonne {
public: 

	Coordonne(double x=0, double y=0);
    
	// Accesseurs
	double getX();
	double getY();
    
	// Mutateurs pour imposer des valeurs hard
	void setX(double x);
	void setY(double y);
    
	// Fonction membres pour un déplacemetn de coordonnées
	void moveX(double deltaX);
	void moveY(double deltaY);

private: 
    double m_x;
    double m_y;
};

#endif //_COORDONNE_H