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
	m_toDelete = true;
}

//Ajouté par Fred
void Charogne::replenishEnergy()
{
	// la charogne est morte, elle n'as donc jamis d'énergie
}

//Ajouté par Fred
void Charogne::seekEnergy()
{
	// la charogne est morte, elle n'as donc jamis d'énergie
}

//Ajouté par Fred
void Charogne::healing()
{
	// La chorogne à toujours 0 points de vie
}

//Ajouté par Fred
void Charogne::receiveDamages(int nbDamage)
{
	// La charogne est déjà morte, il n'est donc pas pertinent de
	// lui infliger des dégats
}

//Ajouté par Fred
void Charogne::reproduction()
{
	// la charogne ne peux pas se reproduire
}

//Ajouté par Fred
void Charogne::simulation()
{
	if (m_age < m_ageMax) {
		m_age++;
	}
	else {
		pourrir();
	}
}

//Ajouté par Fred
void Charogne::dying()
{
	// La charogne est déjà morte
}

//Ajouté par Fred
bool Charogne::isDead()
{
	return true;
}

//Ajouté par Fred
bool Charogne::isDamaged()
{
	return true;
}
