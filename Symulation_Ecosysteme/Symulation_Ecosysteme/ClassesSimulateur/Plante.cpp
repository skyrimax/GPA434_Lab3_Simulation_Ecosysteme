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

bool Plante::healing()
{
	return false;
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

			// S�lection d'une case adjacente au hasard
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
				// Nombre random pour d�terminer si la plante produit un enfant
				chance = dist(mt);

				// D�termination du succ�s de la reproduction
				if (caseAdjacente->getType == Terrain::TypeTerrain::Gazon && chance % ODDS_GAZON == 0) {
					if (caseAdjacente->getRessources() > RESSOURCES_MIN_PLANTE) {
						caseAdjacente->perdreRessources(RESSOURCES_MIN_PLANTE);
						caseAdjacente->setHasPlante(true);

						m_environnement->addPlante(new Plante(m_environnement, /*Ajouter non de plante ici*/ "Arbre",
							/*Ajouter hp ici*/ 1, /*Ajouter energy*/1, /*Ajouter age adulte*/ 10, /*Ajouter age max*/100,
							x, y, /*Ajouter temps reproduction*/ 300));

						hasReproduced = true;
					}
				}
				else if (caseAdjacente->getType == Terrain::TypeTerrain::Terre && chance % ODDS_TERRE == 0) {
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
}

void Plante::simulation()
{
	if (!this->isDead()) {
		this->replenishEnergy();

		if (!this->m_isBeingEaten) {
			this->healing();

		}

		this->reproduction();
	}
	else
	{
		this->dying();
	}
}

void Plante::dying()
{
	// Rien � faire � la mort d'une plante
}

bool Plante::isDead()
{
	return (m_hp <= 0 || (m_age < m_ageAdulte && m_isBeingEaten) || m_age >= m_ageMax);
}
