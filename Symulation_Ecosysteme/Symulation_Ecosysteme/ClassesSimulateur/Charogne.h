/**
 * Project Untitled
 */


#ifndef _CHAROGNE_H
#define _CHAROGNE_H

#include "Vivant.h"
#include "Animal.h"

class Animal; //Ajouté par Fred

class Charogne: public Vivant {
public: 
    
	//Charogne();
	Charogne(Animal *animal);//Ajouté par Fred
	

	// Fonctions membres virtuelles héritées de QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void pourrir();

	/*Ajouté par Fred*/
	// Fonctions membres virtuelles héritées de Vivant
	virtual void replenishEnergy() override;
	virtual void seekEnergy() override;
	virtual void healing() override;
	virtual void receiveDamages(int nbDamage);
	virtual void reproduction() override;
	virtual void simulation() override;
	virtual void dying() override;
	virtual bool isDead() override;
	virtual bool isDamaged();

private: 
	//Ajouté par Fred, couleur des charognes
	QColor sCharognesBackgoundColor;
	//Ajouté par Fred, la forme des charognes
	QPolygonF mshape;
};

#endif //_CHAROGNE_H