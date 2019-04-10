/**
 * Project Untitled
 */


#ifndef _CHAROGNE_H
#define _CHAROGNE_H

#include "Vivant.h"


class Charogne: public Vivant {
public: 
    
	Charogne();

	// Fonctions membres virtuelles h�rit�es de QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
void pourrir();
    
int getTime();

protected:
	//Ajout� par Fred, couleur des charognes
	QColor sCharognesBackgoundColor;
	//Ajout� par Fred, la forme des charognes
	QPolygonF mshape;


private: 
    int time;
};

#endif //_CHAROGNE_H