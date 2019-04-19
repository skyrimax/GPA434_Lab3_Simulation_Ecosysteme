/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Herbivore.h"
#include "Environement.h"
#include <QPainter>
#include <QRandomGenerator>

/**
 * Herbivore implementation
 */
Herbivore::Herbivore(Environnement* environnement, std::string espece, int hp,
	int energy, int ageAdulte, int ageMax, double x, double y,
	double vitesse, double sprint, Sex sex,
	int nbProgenituresMin, int nbProgenituresMax,
	Animal* mere, Meute* meute,
	int timerMort, int tempsGestation, int tempsReproduction,
	std::list<std::string> cible)
	:Animal(environnement, espece, hp, energy, ageAdulte, ageMax, x, y,
		vitesse, sprint, sex, nbProgenituresMin, nbProgenituresMax, mere,
		meute, timerMort, tempsGestation, tempsReproduction, cible),
	m_plante(nullptr)
{
	if (espece == "Chevreuil")
	{
		sHerbivorBackgoundColor.setRgb(255, 255, 0);//Jaune pour les chevreuils
	}
	else
	{
		sHerbivorBackgoundColor.setRgb(255, 0, 127);//Rose pour les lapins
	}
}


QRectF Herbivore::boundingRect() const
{
	
	//Ajouté par Fred,
	return QRectF(-0.25 * scale(), -0.5 * scale(), 1.0 * scale(), 1.25 * scale());

}

void Herbivore::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	
	//Ajouté par Fred
	painter->setPen(Qt::NoPen);
	painter->setBrush(sHerbivorBackgoundColor);
	painter->drawPolygon(mshape);

}

void Herbivore::replenishEnergy()
{
	if (m_energy < m_energyMax && m_plante != nullptr) {
		m_energy += 1 * COUT_FRUIT;

		if (m_energy >= m_energyMax) {
			m_energy = m_energyMax;
		}

		m_plante->receiveDamages(1);
		
	}
	else {
		m_plante = nullptr;
	}
}

void Herbivore::seekEnergy()
{
	if (m_plante == nullptr) {
		chooseTarget();
	}
}

void Herbivore::simulation()
{
	bool didAction = false;

	closestPredateur();

	if (!isDead()) {
		if (m_age < m_ageAdulte) {
			if (m_plante != nullptr) {
				trackTarget();
				if (m_coordonne.getX() == m_plante->getCoordonne().getX(),
					m_coordonne.getY() == m_plante->getCoordonne().getY()) {
					replenishEnergy();
				}
			}
			else if(m_mere != nullptr) //Condition ajouté par Fred
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
			if (m_closestPredateur!=nullptr)//Condition ajouté par Fred
			{
				if (distanceEntre2Points(m_closestPredateur->getCoordonne(),
					m_coordonne) < AWARENESS_CIRCLE) {
					flee();

					didAction = true;
				}
			}
			if (m_hp < 0.9*m_hpMax && !didAction) {
				healing();

				didAction = true;
			}
			if ((m_energy < 0.5*m_energyMax || m_plante != nullptr) && !didAction) {
				if (m_plante == nullptr) {
					seekEnergy();
				}

				if (m_plante != nullptr) {
					trackTarget();

					if (m_coordonne.getX() == m_plante->getCoordonne().getX() &&
						m_coordonne.getY() == m_plante->getCoordonne().getY()) {
						replenishEnergy();
					}

					didAction = true;
				}
			}
			if (((!m_aEnfant || m_timerReproduction == 0) && m_sex == Sex::Male) && !didAction) {
				chooseMate();

				if (m_mate!=nullptr)//Condition ajouté par Fred
				{
					trackMate();
					if (m_coordonne.getX() == m_mate->getCoordonne().getX() &&
						m_coordonne.getY() == m_mate->getCoordonne().getY()) {
						reproduction();

						m_mate->reproduction();
					}

					didAction = true;
				}
			}
			if (m_timerGestation == 0 && m_enceinte && m_sex == Animal::Sex::Female && !didAction) {
				accoucher();
			}
			if (m_sex == Sex::Female && m_enfant.size() != 0 && !didAction) {
				bool needToFindFood = false;

				for (auto const enfant : m_enfant) {
					if (enfant->isHungry()) {
						needToFindFood = true;
					}
				}

				if (needToFindFood || m_plante != nullptr) {
					if (m_plante == nullptr) {
						seekEnergy();
					}

					if (m_plante != nullptr) {
						for (auto const enfant : m_enfant) {
							enfant->chooseTarget(m_plante);
						}

						trackTarget();

						if (m_coordonne.getX() == m_plante->getCoordonne().getX(),
							m_coordonne.getY() == m_plante->getCoordonne().getY()) {
							replenishEnergy();
						}

						didAction = true;
					}
				}
			}
			if (m_hp < m_hpMax && didAction) {
				healing();

				didAction = true;
			}
			if(!didAction) {
				wander();
			}
			m_age++;
			if (m_timerReproduction > 0)
				m_timerReproduction--;
			if (m_enceinte && m_timerGestation > 0)
				m_timerGestation--;
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

	setRotation(m_orientation.getDirection());
}

void Herbivore::chooseTarget()
{
	std::list<Plante*> plantes = m_environnement->getPlantes();
	double distance;
	double distanceMin = INT_MAX;
	Plante* closestPlante=nullptr;

	for (auto const plante : plantes) {
		if (std::find(m_cible.begin(), m_cible.end(), plante->getEspece()) != m_cible.end()) {
			distance = distanceEntre2Points(this->m_coordonne, plante->getCoordonne());

			if (distance < distanceMin) {
				distanceMin = distance;
				closestPlante = plante;
			}
		}
	}

	if (closestPlante != nullptr) {
		closestPlante->getIsEatenBy().push_back(this);
	}

	m_plante = closestPlante;
}

void Herbivore::chooseTarget(Vivant * target)
{
	if (std::find(m_cible.begin(), m_cible.end(), target->getEspece()) != m_cible.end()) {
		m_plante = static_cast<Plante*>(target);
	}
}

void Herbivore::resetTarget()
{
	m_plante = nullptr;
}

void Herbivore::trackTarget()
{
	m_isSprinting = false;

	m_orientation.setVX(m_plante->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_plante->getCoordonne().getY() - m_coordonne.getY());

	deplacer(m_vitesse, m_plante);
}

void Herbivore::removeFromTarget()
{
	m_plante->getIsEatenBy().remove(this);
}

void Herbivore::chooseMate()
{
	Animal* mate = nullptr;
	int distance = INT_MAX;

	if (m_meute == nullptr) {
		for (auto const h : m_environnement->getHerbivores()) {
			if (h->getEspece() == m_espece && h->getMate() == nullptr && h->getenceinte() == false && h->getSex() != m_sex && h->gettimerReproduction() == 0) {
				if (distanceEntre2Points(m_coordonne, h->getCoordonne()) < distance) {
					distance = distanceEntre2Points(m_coordonne, h->getCoordonne());

					mate = h;
				}
			}
		}
	}
	else {
		for (auto const & h : m_meute->getMembres()) {
			if (h->getEspece() == m_espece && h->getMate() == nullptr && h->getenceinte() == false && h->getSex() != m_sex && h->gettimerReproduction() == 0) {
				if (distanceEntre2Points(m_coordonne, h->getCoordonne()) < distance) {
					distance = distanceEntre2Points(m_coordonne, h->getCoordonne());

					mate =h;
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

void Herbivore::trackMate()
{
	m_isSprinting = false;

	m_orientation.setVX(m_mate->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_mate->getCoordonne().getY() - m_coordonne.getY());

	deplacer(m_vitesse, m_mate);
}

void Herbivore::accoucher()
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

		Herbivore* enfant = new Herbivore(m_environnement, m_espece, m_hpMax, m_energyMax,
			m_ageAdulte, m_ageMax, x, y, m_vitesse, m_sprint, sex, m_nbProgenituresMin,
			m_nbProgenituresMax, this, m_meute, m_timerMort, m_tempsGestation,
			m_tempsReproduction, m_cible);

		if (m_meute == nullptr) {
			m_environnement->addHerbivore(enfant);
		}
		else {
			m_meute->addMembre(enfant);
		}
	}

	m_enceinte = false;
}

Vivant * Herbivore::getTarget()
{
	return m_plante;
}
