/**
 * Project Untitled
 */


#ifndef _COORDONNE_H
#define _COORDONNE_H

class Coordonne {
public: 

	Coordonne(double x=0, double y=0);
    
double getX();
    
int getY();
    
void setX();
    
void setY();
    
void moveX();
    
void moveY();
private: 
    double m_x;
    double m_y;
};

#endif //_COORDONNE_H