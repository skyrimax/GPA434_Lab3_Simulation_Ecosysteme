/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Herbivore.h"
#include "Environement.h"
#include <QPainter>

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
{
	//Ajouté par Fred, création d'une flèce pour les herbivores
	mshape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0.)
		<< QPointF(-0.25, -0.5);

	sHerbivorBackgoundColor.setRgb(255,255,0);//Jaune
}


QRectF Herbivore::boundingRect() const
{
	//Ajouté par Fred,
	return QRectF(-0.25, -0.5, 1.0 , 1.25);
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
	if (m_energy<m_energyMax && m_plante->getEnergy()>0) {
		m_plante->receiveDamages(1);

		m_energy += 1 * COUT_FRUIT;
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
			else
			{
				trackMother();
			}
		}
		else if (m_age == m_ageAdulte) {
			devenirAdulte();
		}
		else if (m_age > m_ageAdulte) {
			if (distanceEntre2Points(m_closestPredateur->getCoordonne(),
				m_coordonne) < AWARENESS_CIRCLE) {
				flee();
			}
			else if (m_hp < .9*m_hpMax) {
				healing();
			}
			else if (m_energy < 0.1*m_energyMax) {
				seekEnergy();
				trackTarget();
				if (m_coordonne.getX() == m_plante->getCoordonne().getX(),
					m_coordonne.getY() == m_plante->getCoordonne().getY()) {
					replenishEnergy();
				}
			}
			else if ((!m_aEnfant || m_timerReproduction == 0) && m_sex == Sex::Male) {
				chooseMate();
				trackMate();
				if (m_coordonne.getX() == m_mate->getCoordonne().getX() &&
					m_coordonne.getY() == m_mate->getCoordonne().getY()) {
					reproduction();

					m_mate->reproduction();
				}
			}
			else if (m_sex == Sex::Female && m_enfant.size() != 0) {
				bool needToFindFood = false;

				for (auto const enfant : m_enfant) {
					if (enfant->isHungry()) {
						needToFindFood = true;
					}
				}

				if (needToFindFood) {
					seekEnergy();

					for (auto const enfant : m_enfant) {
						enfant->chooseTarget(m_plante);
					}

					trackTarget();
					if (m_coordonne.getX() == m_plante->getCoordonne().getX(),
						m_coordonne.getY() == m_plante->getCoordonne().getY()) {
						replenishEnergy();
					}
				}
			}
			if (m_hp < m_hpMax) {
				healing();
			}
			else {
				wander();
			}
			m_age++;
			if (m_timerReproduction > 0)
				m_timerReproduction--;
			if (m_enceinte && m_timerGestation > 0)
				m_timerGestation--;
		}
	}
	else if (isDead()) {
		if (m_dead) {
			if (m_timerMort > 0) {
				m_timerMort--;
			}
			else {
				devenirCharogne();
			}
		}
		else
		{
			dying();
		}
	}
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

	m_plante = closestPlante;
}

void Herbivore::chooseTarget(Vivant * target)
{
	m_plante = static_cast<Plante*>(target);
}

void Herbivore::resetTarget()
{
	m_plante = nullptr;
}

void Herbivore::trackTarget()
{
	m_orientation.setVX(m_plante->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_plante->getCoordonne().getY() - m_coordonne.getY());

	walk(this);
}

void Herbivore::chooseMate()
{
	Herbivore* mate = nullptr;
	int distance = INT_MAX;

	std::list<Herbivore*> liste = m_environnement->getHerbivores();

	for (auto const h : liste) {
		if (h->getEspece() == m_espece) {	//Modifié par Fred, h->getEspece est devenue h->getEspece(). Il manquait les paranthèses de la fonction
			if (distanceEntre2Points(m_coordonne, h->getCoordonne()) < distance) {
				distance = distanceEntre2Points(m_coordonne, h->getCoordonne());

				mate = h;
			}
		}
	}
}

void Herbivore::trackMate()
{
	m_orientation.setVX(m_mate->getCoordonne().getX() - m_coordonne.getX());
	m_orientation.setVY(m_mate->getCoordonne().getY() - m_coordonne.getY());

	walk(this);
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
}

Plante * Herbivore::getPlante()
{
	return m_plante;
}
