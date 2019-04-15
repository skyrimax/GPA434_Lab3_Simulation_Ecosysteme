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
		//Ajouté par Fred, création d'une flèce pour les carnivores
	mshape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0.)
		<< QPointF(-0.25, -0.5);

	setPos(QPointF(x, y));
	setScale(5);
	sCarnivoreBackgoundColor.setRgb(255, 128, 0);//Orange
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
	
	setPos(QPointF(m_coordonne.getX()+1,m_coordonne.getY()+1));
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

		for (auto const proie : m_environnement->getCharognards()) {
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
	Animal* mate = nullptr;
	int distance = INT_MAX;

	if (m_meute = nullptr) {
		for (auto const c : m_environnement->getCarnivores()) {
			if (c->getEspece() == m_espece && c->getMate() == nullptr && c->getenceinte() == false && c->getSex() != m_sex) {
				if (distanceEntre2Points(m_coordonne, c->getCoordonne()) < distance) {
					distance = distanceEntre2Points(m_coordonne, c->getCoordonne());

					mate = c;
				}
			}
		}
	}
	else {
		for (auto const & c : m_meute->getMembres()) {
			if (c->getEspece() == m_espece && c->getMate() == nullptr && c->getenceinte() == false && c->getSex() != m_sex) {
				if (distanceEntre2Points(m_coordonne, c->getCoordonne()) < distance) {
					distance = distanceEntre2Points(m_coordonne, c->getCoordonne());

					mate = c;
				}
			}
		}
	}

	if (mate->chooseMate(this)) {
		m_mate = mate;
	}
}

void Carnivore::trackMate()
{
	m_isSprinting = false;

	m_orientation.setVX(m_mate->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_mate->getCoordonne().getY() - m_coordonne.getY());

	deplacer(m_vitesse, m_mate);
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

	sex = dist(mt) % 2 == 0 ? Animal::Sex::Male : Animal::Sex::Female;

	for (int i = 0; i < nbProgenitures; i++) {
		x = m_coordonne.getX() - m_orientation.getUnitX()*DÉCALAGE_ACCOUCHEMENT*i;
		y = m_coordonne.getY() - m_orientation.getUnitY()*DÉCALAGE_ACCOUCHEMENT*i;

		Carnivore* enfant = new Carnivore(m_environnement, m_espece, m_hpMax, m_energyMax,
			m_ageAdulte, m_ageMax, x, y, m_vitesse, m_sprint, sex, m_nbProgenituresMin,
			m_nbProgenituresMax, this, m_meute, m_timerMort, m_tempsGestation,
			m_tempsReproduction, m_cible, m_isCharognard);

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