/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Plante.h"
#include "Herbivore.h"
#include "Terrain.h"
#include "Environement.h"

/**
 * Plante implementation
 */

Plante::Plante(Environnement * environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax, int x, int y,
	int timeToReproduction)
	:Vivant(environnement, espece, hp, energy, ageAdulte, ageMax, x, y),
	m_timeToReproduction(timeToReproduction), m_timer(timeToReproduction), m_fruits(0), m_isBeingEaten(false)
{
}

QRectF Plante::boundingRect() const
{
	return QRectF();
}

void Plante::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void Plante::replenishEnergy()
{
	m_energy += ENERGY_REGEN_PLANTE;
	if (m_energy > m_energyMax)
		m_energy = m_energyMax;
}

void Plante::seekEnergy()
{
	// Plants passively receive energy
}

void Plante::healing()
{
	if (m_hpMax - m_hp >= RATE_GUERISON)
	{
		if (m_energy > COUT_GUERISON*RATE_GUERISON) {
			m_energy -= COUT_GUERISON * RATE_GUERISON;
			m_hp += RATE_GUERISON;
		}
	}
	else {
		if (m_energy > (m_hpMax - m_hp)*COUT_GUERISON) {
			m_energy -= (m_hpMax - m_hp)*COUT_GUERISON;
			m_hp = m_hpMax;
		}
	}
}

void Plante::receiveDamages(int nbDamage)
{
}

void Plante::reproduction()
{
	bool hasReproduced = false;
	int x = m_coordonne.getX();
	int y = m_coordonne.getY();
	int chance;

	Terrain *caseAdjacente;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, INT_MAX);

	if (m_timer == 0 && m_fruits > 0 && !m_isBeingEaten) {
		do {
			m_fruits--;

			// Sélection d'une case adjacente au hasard
			switch (dist(mt)%4)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			default: // n'arrive jamais;
				break;
			}

			caseAdjacente = m_environnement->getTerrain(x, y);

			if (!caseAdjacente->hasPlante()) {
				// Nombre random pour déterminer si la plante produit un enfant
				chance = dist(mt);

				// Détermination du succès de la reproduction
				if (caseAdjacente->getType() == Terrain::TypeTerrain::Gazon && chance % ODDS_GAZON == 0) {
					if (caseAdjacente->getRessources() > RESSOURCES_MIN_PLANTE) {
						caseAdjacente->perdreRessources(RESSOURCES_MIN_PLANTE);
						caseAdjacente->setHasPlante(true);

						m_environnement->addPlante(new Plante(m_environnement, /*Ajouter non de plante ici*/ "Arbre",
							/*Ajouter hp ici*/ 1, /*Ajouter energy*/1, /*Ajouter age adulte*/ 10, /*Ajouter age max*/100,
							x, y, /*Ajouter temps reproduction*/ 300));

						hasReproduced = true;
					}
				}
				else if (caseAdjacente->getType() == Terrain::TypeTerrain::Terre && chance % ODDS_TERRE == 0) {
					caseAdjacente->setType(Terrain::TypeTerrain::Gazon);
					caseAdjacente->reprendreRessources();
					
					caseAdjacente->perdreRessources(RESSOURCES_MIN_PLANTE);
					caseAdjacente->setHasPlante(true);

					m_environnement->addPlante(new Plante(m_environnement, /*Ajouter non de plante ici*/ "Arbre",
						/*Ajouter hp ici*/ 1, /*Ajouter energy*/1, /*Ajouter age adulte*/ 10, /*Ajouter age max*/100,
						x, y, /*Ajouter temps reproduction*/ 300));

					hasReproduced = true;
				}
			}


		} while (m_fruits>0 && !hasReproduced);
	}

	m_timer = m_timeToReproduction;
}

void Plante::simulation()
{
	if (!this->isDead()) {
		this->replenishEnergy();

		if (!this->m_isBeingEaten && this->isDamaged()) {
			this->healing();
		}
		else {
			this->reproduction();
		}
	}
	else
	{
		this->dying();
	}

	m_timer--;
}

void Plante::dying()
{
	m_environnement->getTerrain(m_coordonne.getX(), m_coordonne.getY())->
		gainRessources(m_hp*HP_TO_RESSOURCE_RATE + m_energy * COUT_GUERISON*HP_TO_RESSOURCE_RATE);
}

bool Plante::isDead()
{
	return (m_hp <= 0 || (m_age < m_ageAdulte && m_isBeingEaten) || m_age >= m_ageMax);
}

bool Plante::isDamaged()
{
	return m_hp<m_hpMax;
}
