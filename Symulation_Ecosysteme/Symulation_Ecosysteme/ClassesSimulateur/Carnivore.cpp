/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Carnivore.h"
#include "Environement.h"

/**
 * Carnivore implementation
 */

QRectF Carnivore::boundingRect() const
{
	return QRectF();
}

void Carnivore::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
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

	proie = closestHerbivore;
}

void Carnivore::chooseTarget(Vivant* target)
{
	proie = static_cast<Herbivore*>(target);
}

void Carnivore::resetTarget()
{
	proie = nullptr;
}

void Carnivore::trackTarget()
{
	m_orientation.setVX(proie->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(proie->getCoordonne().getY() - m_coordonne.getY());

	walk();
}

void Carnivore::chooseMate()
{
	Carnivore* mate = nullptr;
	int distance = INT_MAX;

	std::list<Carnivore*> liste = m_environnement->getCarnivores();

	for (auto const h : liste) {
		if (h->getEspece == m_espece) {
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

	walk();
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
