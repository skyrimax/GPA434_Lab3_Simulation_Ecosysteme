/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Meute.h"
#include "Environement.h"


 /**
  * Meute implementation
  */

std::list<Animal*>& Meute::getMembres()
{
	return m_membres;
}

std::list<Animal*> Meute::simulation()
{
	bool flagFlee=false;
	bool continueEating = true;
	bool healing = false;
	bool healingCritical = false;

	std::list<Animal*> deads;

	if (m_alpha == nullptr) {
		setAlpha();
	}

	for (auto const & membre : m_membres) {
		membre->closestPredateur();
		if (distanceEntre2Points(membre->getclosestPredateur()->getCoordonne(),
			membre->getCoordonne()) < AWARENESS_CIRCLE) {
			flagFlee = true;
		}

		if (membre->getEnergy() < 0.1*membre->getEnergyMax()) {
			faim = true;
		}

		if (membre->getHp() < membre->getHpMax()) {
			healing = true;
		}

		if (membre->getHp() < 0.9*membre->getHpMax()) {
			healingCritical = true;
		}
	}

	for (auto const & membre : m_membres) {
		if (faim && membre->getEnergy() == membre->getEnergyMax()) {
			continueEating = false;
		}
	}

	faim = continueEating;

	if (!m_alpha->isDead()) {
		if (faim && !healingCritical) {
			m_alpha->seekEnergy();
			m_alpha->trackTarget();
		}
		else if (m_alpha->getaEnfant() || m_alpha->gettimerReproduction()) {
			m_alpha->chooseMate();
			m_alpha->trackMate();
			if (m_alpha->getCoordonne().getX() == m_alpha->getMate()->getCoordonne().getX() &&
				m_alpha->getCoordonne().getY() == m_alpha->getMate()->getCoordonne().getY()) {
				m_alpha->reproduction();

				m_alpha->getMate()->reproduction();
			}
		}
		else {
			m_alpha->wander();
		}
	}
	else {
		if (m_alpha->getDead()) {
			if (m_alpha->gettimerMort()) {
				m_alpha->gettimerMort();
			}
			else {
				m_alpha->devenirCharogne();
			}
		}
		else {
			m_alpha->dying();
		}
	}

	(m_alpha->getAge())++;
	if (m_alpha->gettimerReproduction() > 0)
		(m_alpha->gettimerReproduction())--;

	for (auto const & membre : m_membres) {
		if (!membre->isDead() && membre != m_alpha) {
			if (membre->getAge() <= membre->getAgeAdulte()) {
				membre->simulation();
			}
			else if (flagFlee) {
				membre->flee();
			}
			else if (healingCritical) {
				membre->healing();
			}
			else if (faim) {
				membre->chooseTarget(m_alpha->getTarget());

				membre->trackTarget();
				if (membre->getCoordonne().getX() == membre->getTarget()->getCoordonne().getX() &&
					membre->getCoordonne().getY() == membre->getTarget()->getCoordonne().getY()) {
					membre->replenishEnergy();
				}
			}
			else if (membre == m_alpha->getMate()) {
				membre->trackMate();
			}
			else if (healing) {
				membre->healing();
			}

			(membre->getAge())++;
			if (membre->gettimerGestation() > 0)
				(membre->gettimerGestation())--;
		}
		else if (membre->isDead() && membre != m_alpha) {
			if (membre->getDead()) {
				if (membre->gettimerMort() > 0) {
					(membre->gettimerMort())--;
				}
				else {
					membre->devenirCharogne();
				}
			}
			else {
				membre->dying();
			}
		}
	}

	for (auto const & membre : m_membres) {
		if (membre->toDelete()) {
			deads.push_back(membre);
		}
	}

	return deads;
}

void Meute::addMembre(Animal * membre)
{
	m_membres.push_back(membre);

	m_environnement->addVivant(membre);

	m_environnement->addItem(membre);
}

Animal * Meute::getAlpha()
{
	return m_alpha;
}

void Meute::setAlpha()
{
	for (auto const membre : m_membres) {

		if (membre->getSex() == Animal::Sex::Male && membre->getAge() >= membre->getAgeAdulte()) {
			m_alpha = membre;
			break;
		}
	}

}


