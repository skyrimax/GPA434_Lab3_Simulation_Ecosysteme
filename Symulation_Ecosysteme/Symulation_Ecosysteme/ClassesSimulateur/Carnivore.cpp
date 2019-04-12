/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Carnivore.h"
#include "Environement.h"
#include <QPainter>

/**
 * Carnivore implementation
 */

Carnivore::Carnivore(Environnement* environnement, std::string espace, int hp, int energy, int ageAdulte, int ageMax,
	double x, double y, double vitesse, double sprint, Sex sex, int nbProgenituresMin, int nbProgenituresMax,
	Animal * mere, Meute * meute, int timerMort, int tempsGestation, int tempsReproduction, std::list<std::string>cible)
{
	// ************** À IMPLANTER ***************

		//Ajouté par Fred, création d'une flèce pour les carnivores
	mshape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0.)
		<< QPointF(-0.25, -0.5);

	sCarnivoreBackgoundColor.setRgb(153, 0, 153);//Mauve
}

/*Ajouté par Fred*/
bool Carnivore::isCharognard()
{
	return m_isCharognard;
}

QRectF Carnivore::boundingRect() const
{
	//Ajouté par Fred,
	return QRectF(-0.25, -0.5, 1.0, 1.25);
}

void Carnivore::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ajouté par Fred
	painter->setPen(Qt::NoPen);
	painter->setBrush(sCarnivoreBackgoundColor);
	painter->drawPolygon(mshape);
}


void Carnivore::replenishEnergy()
{
	// ************** À IMPLANTER ***************
}

void Carnivore::seekEnergy()
{
	// ************** À IMPLANTER ***************
}

void Carnivore::simulation()
{
	// ************** À IMPLANTER ***************
}

void Carnivore::chooseTarget()
{
	std::list<Herbivore*> proies = m_environnement->getHerbivores();
	double distance;
	double distanceMin = INT_MAX;
	Animal* closestHerbivore = nullptr;

	for (auto const proie : proies) {
		if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
			distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

			if (distance < distanceMin) {
				distanceMin = distance;
				closestHerbivore = proie;
			}
		}
	}

	m_proie = closestHerbivore;
}

void Carnivore::chooseTarget(Vivant* target)
{
	m_proie = static_cast<Herbivore*>(target);
}

void Carnivore::resetTarget()
{
	m_proie = nullptr;
}

void Carnivore::trackTarget()
{
	m_orientation.setVX(m_proie->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_proie->getCoordonne().getY() - m_coordonne.getY());

	walk(this);
}

void Carnivore::removeFromTarget()
{
	//À implémenter
}

void Carnivore::chooseMate()
{
	Carnivore* mate = nullptr;
	int distance = INT_MAX;

	std::list<Carnivore*> liste = m_environnement->getCarnivores();

	for (auto const h : liste) {
		if (h->getEspece() == m_espece) {	//Modifié par Fred, h->getEspece est devenu h->getEspece()
			if (distanceEntre2Points(m_coordonne, h->getCoordonne()) < distance) {
				distance = distanceEntre2Points(m_coordonne, h->getCoordonne());

				mate = h;
			}
		}
	}

	m_mate = mate;
}

void Carnivore::trackMate()
{
	m_orientation.setVX(m_mate->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_mate->getCoordonne().getY() - m_coordonne.getY());

	walk(this);
}

void Carnivore::accoucher()
{
	int nbProgenitures;
	double x;
	double y;
	Sex sex;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(m_nbProgenituresMin, m_nbProgenituresMax);

	nbProgenitures = dist(mt);

	for (int i = 0; i < nbProgenitures; i++) {
		x = m_coordonne.getX() - m_orientation.getUnitX()*DÉCALAGE_ACCOUCHEMENT*i;
		y = m_coordonne.getY() - m_orientation.getUnitY()*DÉCALAGE_ACCOUCHEMENT*i;

		Carnivore* enfant = new Carnivore(m_environnement, m_espece, m_hpMax, m_energyMax,
			m_ageAdulte, m_ageMax, x, y, m_vitesse, m_sprint, sex, m_nbProgenituresMin,
			m_nbProgenituresMax, this, m_meute, m_timerMort, m_tempsGestation,
			m_tempsReproduction, m_cible);

		if (m_meute == nullptr) {
			m_environnement->addCarnivore(enfant);
		}
		else {
			m_meute->addMembre(enfant);
		}
	}
}


Vivant * Carnivore::getTarget()
{
	return m_proie;
}