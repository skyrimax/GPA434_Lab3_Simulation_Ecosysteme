/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Charogne.h"
#include <QPainter>


/**
 * Charogne implementation
 */

//Modification du param�tre par Fred
Charogne::Charogne(Animal *animal)
{
	//Ajout� par Fred, cr�ation d'une fl�ce pour les charogne
	mshape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0.)
		<< QPointF(-0.25, -0.5);

	sCharognesBackgoundColor.setRgb(255, 0, 0);
}


QRectF Charogne::boundingRect() const
{
	//Ajout� par Fred,
	return QRectF(-0.25, -0.5, 1.0, 1.25);
}

void Charogne::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ajout� par Fred
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

//Ajout� par Fred
void Charogne::replenishEnergy()
{
	
}

//Ajout� par Fred
void Charogne::seekEnergy()
{
}

//Ajout� par Fred
void Charogne::healing()
{

}

//Ajout� par Fred
void Charogne::receiveDamages(int nbDamage)
{

}

//Ajout� par Fred
void Charogne::reproduction()
{

}

//Ajout� par Fred
void Charogne::simulation()
{

}

//Ajout� par Fred
void Charogne::dying()
{

}

//Ajout� par Fred
bool Charogne::isDead()
{
	return true;
}

//Ajout� par Fred
bool Charogne::isDamaged()
{
	return false;
}
