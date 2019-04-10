/**
 * Project Untitled
 */


#ifndef _CHAROGNE_H
#define _CHAROGNE_H

#include "Vivant.h"


class Charogne: public Vivant {
public: 
    
	Charogne();

	// Fonctions membres virtuelles héritées de QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
void pourrir();
    
int getTime();

protected:
	//Ajouté par Fred, couleur des charognes
	QColor sCharognesBackgoundColor;
	//Ajouté par Fred, la forme des charognes
	QPolygonF mshape;


private: 
    int time;
};

#endif //_CHAROGNE_H