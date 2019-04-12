/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Charogne.h"
#include <QPainter>


/**
 * Charogne implementation
 */

//Modification du paramètre par Fred
Charogne::Charogne(Animal *animal)
{
	//Ajouté par Fred, création d'une flèce pour les charogne
	mshape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0.)
		<< QPointF(-0.25, -0.5);

	sCharognesBackgoundColor.setRgb(255, 0, 0);
}


QRectF Charogne::boundingRect() const
{
	//Ajouté par Fred,
	return QRectF(-0.25, -0.5, 1.0, 1.25);
}

void Charogne::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ajouté par Fred
	painter->setPen(Qt::NoPen);
	painter->setBrush(sCharognesBackgoundColor);
	painter->drawPolygon(mshape);
}

/**
 * @return void
 */
void Charogne::pourrir() {
    return;
}

/**
 * @return int
 */
int Charogne::getTime() {
    return 0;
}

//Ajouté par Fred
void Charogne::replenishEnergy()
{
	
}

//Ajouté par Fred
void Charogne::seekEnergy()
{
}

//Ajouté par Fred
void Charogne::healing()
{

}

//Ajouté par Fred
void Charogne::receiveDamages(int nbDamage)
{

}

//Ajouté par Fred
void Charogne::reproduction()
{

}

//Ajouté par Fred
void Charogne::simulation()
{

}

//Ajouté par Fred
void Charogne::dying()
{

}

//Ajouté par Fred
bool Charogne::isDead()
{
	return true;
}

//Ajouté par Fred
bool Charogne::isDamaged()
{
	return false;
}
