/**
 * Project Untitled
 */


#ifndef _CHAROGNE_H
#define _CHAROGNE_H

#include "Vivant.h"


class Charogne: public Vivant {
public: 
    
void pourrir();
    
int getTime();

protected:
	//Ajouté par Fred, couleur des charognes
	static const QColor sCharognesBackgoundColor;

private: 
    int time;
};

#endif //_CHAROGNE_H