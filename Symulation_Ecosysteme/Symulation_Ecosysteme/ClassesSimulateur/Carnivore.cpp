/*
Cette classer est dérivé de la classe Animal. Cette classer contient la fonction simulation qui va faire
la simulation pour chaque carnivore selon leur état et leurs besoins. Elle contient aussi
des fonctions pour trouver et s'orienter vers son herbivore, son carnivore ou le charognard le plus proche.
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
	if (m_energy < m_energyMax && m_proie != nullptr) {
		m_energy += 1 * COUT_GUERISON;

		if (m_energy >= m_energyMax) {
			m_energy = m_energyMax;
		}
	}
	else
	{
		m_proie = nullptr;
	}
}

void Carnivore::seekEnergy()
{
	if (m_proie == nullptr) {
		chooseTarget();
	}
}

void Carnivore::simulation()
{
	closestPredateur();
	if (!isDead()) {
		if (m_age < m_ageAdulte) {
			if (m_proie != nullptr) {
				trackTarget();
				if (m_coordonne.getX() == m_proie->getCoordonne().getX(),
					m_coordonne.getY() == m_proie->getCoordonne().getY()) {
					replenishEnergy();
				}
			}
			else if (m_mere != nullptr) //Condition ajouté par Fred
			{
				trackMother();
			}

			m_age++;
		}
		else if (m_age == m_ageAdulte) {
			devenirAdulte();

			m_age++;
		}
		else if (m_age > m_ageAdulte) {
			if (m_closestPredateur != nullptr)//Condition ajouté par Fred
			{
				if (distanceEntre2Points(m_closestPredateur->getCoordonne(),
					m_coordonne) < AWARENESS_CIRCLE) {
					flee();
				}
			}
			else if (m_hp < 0.9*m_hpMax) {
				healing();
			}
			else if (m_energy < 0.1*m_energyMax || m_proie != nullptr) {
				if (m_proie == nullptr) {
					seekEnergy();
				}

				if (m_proie != nullptr) {
					trackTarget();

					if (m_coordonne.getX() == m_proie->getCoordonne().getX() &&
						m_coordonne.getY() == m_proie->getCoordonne().getY()) {
						replenishEnergy();
					}
				}
			}

			else if ((!m_aEnfant || m_timerReproduction == 0) && m_sex == Sex::Male) {
				chooseMate();
				if (m_mate != nullptr)//Condition ajouté par Fred
				{
					trackMate();
					if (m_coordonne.getX() == m_mate->getCoordonne().getX() &&
						m_coordonne.getY() == m_mate->getCoordonne().getY()) {
						reproduction();

						m_mate->reproduction();
					}
				}
			}
			else if (m_timerGestation == 0 && m_enceinte && m_sex == Animal::Sex::Female) {
				accoucher();
			}
			else if (m_sex == Sex::Female && m_enfant.size() != 0) {
				bool needToFindFood = false;

				for (auto const enfant : m_enfant) {
					if (enfant->isHungry()) {
						needToFindFood = true;
					}
				}

				if (needToFindFood || m_proie != nullptr) {
					if (m_proie == nullptr) {
						seekEnergy();
					}

					for (auto const enfant : m_enfant) {
						enfant->chooseTarget(m_proie);
					}

					trackTarget();
					if (m_coordonne.getX() == m_proie->getCoordonne().getX(),
						m_coordonne.getY() == m_proie->getCoordonne().getY()) {
						replenishEnergy();
					}
				}
			}
		}

		m_energy -= CONSOMMATION_IDLE;
		if (m_energy < 0) {
			m_energy = 0;

			m_hp -= CONSOMMATION_IDLE;
			if (m_hp < 0) {
				m_hp = 0;
			}
		}
	}
	else {
		if (m_dead) {
			if (m_timerMort > 0) {
				m_timerMort--;
			}
			else {
				devenirCharogne();
			}
		}
		else {
			dying();
		}
	}
	setPos(m_coordonne.getX(), m_coordonne.getY());

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

	if (closestProie != nullptr) {
		if (typeid(closestProie) == typeid(Herbivore) || typeid(closestProie) == typeid(Carnivore)) {
			static_cast<Animal*>(closestProie)->getPredateur().push_back(this);
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

	if (m_meute == nullptr) {
		for (auto const c : m_environnement->getCarnivores()) {
			if (c->getEspece() == m_espece && c->getMate() == nullptr && c->getenceinte() == false && c->getSex() != m_sex && c->gettimerReproduction() == 0) {
				if (distanceEntre2Points(m_coordonne, c->getCoordonne()) < distance) {
					distance = distanceEntre2Points(m_coordonne, c->getCoordonne());

					mate = c;
				}
			}
		}
	}
	else {
		for (auto const & c : m_meute->getMembres()) {
			if (c->getEspece() == m_espece && c->getMate() == nullptr && c->getenceinte() == false && c->getSex() != m_sex && c->gettimerReproduction() == 0) {
				if (distanceEntre2Points(m_coordonne, c->getCoordonne()) < distance) {
					distance = distanceEntre2Points(m_coordonne, c->getCoordonne());

					mate = c;
				}
			}
		}
	}

	if (mate != nullptr) {
		if (mate->chooseMate(this)) {
			m_mate = mate;
		}
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

	m_enceinte = false;
}

Vivant * Carnivore::getTarget()
{
	return m_proie;
}