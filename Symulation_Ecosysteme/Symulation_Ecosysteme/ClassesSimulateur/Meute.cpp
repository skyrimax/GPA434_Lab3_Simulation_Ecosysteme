/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Meute.h"


 /**
  * Meute implementation
  */

void Meute::simulation()
{

	for (auto const membre : m_membres) {
		if (distanceEntre2Points(membre->getclosestPredateur.getCoordonne(), membre->getCoordonne()) < AWARENESS_CIRCLE) {
			if (distanceEntre2Points(m_alpha->getCoordonne(), membre->getCoordonne()) > DISTANCE_ALPHA) {
				membre->flee();
			}
			else {
				for (auto const membre2 : m_membres) {
					if (distanceEntre2Points(m_alpha->getCoordonne(), membre2->getCoordonne()) < DISTANCE_ALPHA &&
						membre != m_alpha) {
						membre->flee();
					}
				}
				m_alpha->flee();
			}
		}
		else if (membre->getEnergy() < 0.1*(membre->getEnergyMax())) {
			m_alpha->seekEnergy();
			m_alpha->trackTarget();
			for (const auto membre : m_membres) {
				if (distanceEntre2Points(m_alpha->getCoordonne(), membre->getCoordonne()) < DISTANCE_ALPHA) {
					membre->setOrientation(m_alpha->getOrientation());
					membre->walk();
				}
				else {
					membre->sprintAlpha();
				}
			}
			/* Virguler dans le if ??.... C'est un && ?*/
			if (m_alpha->getCoordonne.getX() == m_alpha->getPlante()->getCoordonne().getX(),		/*À voir, pas capable d'acceder à m_plante comme l'herbivore*/
				m_alpha->getCoordonne.getY() == m_alpha->getPlante()->getCoordonne().getX()) {
				for (const auto membre : m_membres) {
					if (distanceEntre2Points(m_alpha->getCoordonne(), membre->getCoordonne()) < DISTANCE_ALPHA) {
						membre->replenishEnergy();
					}
				}
			}
		}
		else {
			/***********************************************************************************************************/
			/***********************************************************************************************************/
			/***********************************************************************************************************/
			if (!membre->isDead()) {
				if (membre->getAge() < membre->getAgeAdulte()) {

					membre->trackMother();

				}
				else if (membre->getAge() == membre->getAgeAdulte()) {
					membre->devenirAdulte();
				}
				else if (membre->getAge() > membre->getAgeAdulte()) {

					if (membre->getHp() < .9*membre->getHpMax()) {//On va healer peu importe l'énergie à la sortie du else fi. C'est tu vraiment nécessaire.
						membre->healing();
					}
					
					else if ((!membre->getaEnfant() || membre->gettimerReproduction() == 0) && membre->getSex() == Animal::Sex::Male) {
						membre->chooseMate();
						membre->trackMate();
						if (membre->getCoordonne().getX() == membre->getMate()->getCoordonne().getX() &&
							membre->getCoordonne().getY() == membre->getMate()->getCoordonne().getY()) {
							membre->reproduction();

							membre->getMate()->reproduction();
						}
					}
					//else if (m_sex == Sex::Female && m_enfant.size() != 0) {
					//	bool needToFindFood = false;

					//	for (auto const enfant : m_enfant) {
					//		if (enfant->isHungry()) {
					//			needToFindFood = true;
						//	}
					//	}

					//	if (needToFindFood) {
					//		seekEnergy();

					//		for (auto const enfant : m_enfant) {
					//			enfant->chooseTarget(m_plante);
					//		}

					//		trackTarget();
					//		if (m_coordonne.getX() == m_plante->getCoordonne().getX(),
					//			m_coordonne.getY() == m_plante->getCoordonne().getY()) {
					//			replenishEnergy();
					//		}
					//	}
				}
				if (membre->getHp() < membre->getHpMax()) {
					membre->healing();
				}
				else {
					if (membre->getCoordonne().getX == m_alpha->getCoordonne().getX &&
						membre->getCoordonne().getY == m_alpha->getCoordonne().getY) {
						membre->wander();
					}
					else if (distanceEntre2Points(m_alpha->getCoordonne(), membre->getCoordonne()) > DISTANCE_ALPHA) {
						membre->trackAlpha();
					}
					else {
						membre->sprintAlpha();
					}

				}
				(membre->setAge(membre->getAge() + 1));
				if (membre->gettimerReproduction() > 0)
					membre->settimerReproduction(membre->gettimerReproduction() - 1);
				if (membre->getenceinte() && membre->gettimerGestation() > 0)
					membre->settimerGestation(membre->gettimerGestation() - 1);

			}
			else if (membre->isDead()) {
				if (membre->gettimerMort() > 0) {
					membre->settimerMort(membre->gettimerMort() - 1);
				}
				else {
					membre->devenirCharogne();
				}
			}
		}
		/***********************************************************************************************************/
		/***********************************************************************************************************/
		/***********************************************************************************************************/
	}
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


