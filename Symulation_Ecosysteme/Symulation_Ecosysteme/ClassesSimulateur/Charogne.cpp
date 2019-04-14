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
	: Vivant()
{
	m_hp = 0;
	m_hpMax = 0;
	m_energy = 0;
	m_energyMax = 0;
	m_age = 0;
	m_ageAdulte = 0;
	m_ageMax = AGE_MAX_CHAROGNE;
	m_dead = false;
	m_toDelete = false;
	m_coordonne.setX(animal->getCoordonne().getX());
	m_coordonne.setY(animal->getCoordonne().getY());
	m_environnement = animal->getEnvironnement();
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
	m_toDelete = true;
}

//Ajout� par Fred
void Charogne::replenishEnergy()
{
	// la charogne est morte, elle n'as donc jamis d'�nergie
}

//Ajout� par Fred
void Charogne::seekEnergy()
{
	// la charogne est morte, elle n'as donc jamis d'�nergie
}

//Ajout� par Fred
void Charogne::healing()
{
	// La chorogne � toujours 0 points de vie
}

//Ajout� par Fred
void Charogne::receiveDamages(int nbDamage)
{
	// La charogne est d�j� morte, il n'est donc pas pertinent de
	// lui infliger des d�gats
}

//Ajout� par Fred
void Charogne::reproduction()
{
	// la charogne ne peux pas se reproduire
}

//Ajout� par Fred
void Charogne::simulation()
{
	if (m_age < m_ageMax) {
		m_age++;
	}
	else {
		pourrir();
	}
}

//Ajout� par Fred
void Charogne::dying()
{
	// La charogne est d�j� morte
}

//Ajout� par Fred
bool Charogne::isDead()
{
	return true;
}

//Ajout� par Fred
bool Charogne::isDamaged()
{
	return true;
}
