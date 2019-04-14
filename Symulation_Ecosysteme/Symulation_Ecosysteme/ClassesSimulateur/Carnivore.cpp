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

Carnivore::Carnivore(Environnement* environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax,
	double x, double y, double vitesse, double sprint, Sex sex, int nbProgenituresMin, int nbProgenituresMax,
	Animal * mere, Meute * meute, int timerMort, int tempsGestation, int tempsReproduction, std::list<std::string>cible,
	bool isCharognard)
	: Animal(environnement, espece, hp, energy, ageAdulte, ageMax, x, y,
		vitesse, sprint, sex, nbProgenituresMin, nbProgenituresMax, mere,
		meute, timerMort, tempsGestation, tempsReproduction, cible),
	m_isCharognard(isCharognard), m_proie(nullptr)
{
		//Ajout� par Fred, cr�ation d'une fl�ce pour les carnivores
	mshape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0.)
		<< QPointF(-0.25, -0.5);

	sCarnivoreBackgoundColor.setRgb(153, 0, 153);//Mauve
}

bool Carnivore::isCharognard()
{
	return m_isCharognard;
}

QRectF Carnivore::boundingRect() const
{
	//Ajout� par Fred,
	return QRectF(-0.25, -0.5, 1.0, 1.25);
}

void Carnivore::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ajout� par Fred
	painter->setPen(Qt::NoPen);
	painter->setBrush(sCarnivoreBackgoundColor);
	painter->drawPolygon(mshape);
}

void Carnivore::replenishEnergy()
{
	// ************** � IMPLANTER ***************
}

void Carnivore::seekEnergy()
{
	// ************** � IMPLANTER ***************
}

void Carnivore::simulation()
{
	// ************** � IMPLANTER ***************
}

void Carnivore::chooseTarget()
{
	double distance;
	double distanceMin = INT_MAX;
	Vivant* closestProie = nullptr;

	if (m_isCharognard) {
		for (auto const & charogne : m_environnement->getCharognes()) {
			if (std::find(m_cible.begin(), m_cible.end(), charogne->getEspece()) != m_cible.end()) {
				distance = distanceEntre2Points(this->m_coordonne, charogne->getCoordonne());

				if (distance < distanceMin) {
					distanceMin = distance;
					closestProie = charogne;
				}
			}
		}
	}
	else {
		for (auto const proie : m_environnement->getCarnivores()) {
			if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
				distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

				if (distance < distanceMin) {
					distanceMin = distance;
					closestProie = proie;
				}
			}
		}

		for (auto const & meute : m_environnement->getMeutesCarnivores()) {
			for (auto const proie : meute->getMembres()) {
				if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
					distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

					if (distance < distanceMin) {
						distanceMin = distance;
						closestProie = proie;
					}
				}
			}
		}

		for (auto const proie : m_environnement->getCharognards) {
			if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
				distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

				if (distance < distanceMin) {
					distanceMin = distance;
					closestProie = proie;
				}
			}
		}

		for (auto const & meute : m_environnement->getMeutesCharognards()) {
			for (auto const proie : meute->getMembres()) {
				if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
					distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

					if (distance < distanceMin) {
						distanceMin = distance;
						closestProie = proie;
					}
				}
			}
		}

		for (auto const proie : m_environnement->getHerbivores()) {
			if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
				distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

				if (distance < distanceMin) {
					distanceMin = distance;
					closestProie = proie;
				}
			}
		}

		for (auto const & meute : m_environnement->getMeutesHerbivores()) {
			for (auto const proie : meute->getMembres()) {
				if (std::find(m_cible.begin(), m_cible.end(), proie->getEspece()) != m_cible.end()) {
					distance = distanceEntre2Points(this->m_coordonne, proie->getCoordonne());

					if (distance < distanceMin) {
						distanceMin = distance;
						closestProie = proie;
					}
				}
			}
		}
	}

	m_proie = closestProie;
}

void Carnivore::chooseTarget(Vivant* target)
{
	if (std::find(m_cible.begin(), m_cible.end(), target->getEspece()) != m_cible.end()) {
		m_proie = (target);
	}
}

void Carnivore::resetTarget()
{
	m_proie = nullptr;
}

void Carnivore::trackTarget()
{
	m_orientation.setVX(m_proie->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_proie->getCoordonne().getY() - m_coordonne.getY());

	if (distanceEntre2Points(m_coordonne, m_proie->getCoordonne()) < RANGE_SPRINT) {
		deplacer(m_sprint, m_proie);
	}
	else {
		deplacer(m_vitesse, m_proie);
	}
}

void Carnivore::removeFromTarget()
{
	if (typeid(*m_proie) == typeid(Herbivore) || typeid(*m_proie) == typeid(Carnivore)) {
		static_cast<Animal*>(m_proie)->getPredateur().remove(this);
	}
}

void Carnivore::chooseMate()
{
	Carnivore* mate = nullptr;
	int distance = INT_MAX;

	std::list<Carnivore*> liste = m_environnement->getCarnivores();

	for (auto const h : liste) {
		if (h->getEspece() == m_espece) {
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
		x = m_coordonne.getX() - m_orientation.getUnitX()*D�CALAGE_ACCOUCHEMENT*i;
		y = m_coordonne.getY() - m_orientation.getUnitY()*D�CALAGE_ACCOUCHEMENT*i;

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
