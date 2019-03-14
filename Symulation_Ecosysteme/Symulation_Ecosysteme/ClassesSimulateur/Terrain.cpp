/**
 * Project Untitled
 */

#include "stdafx.h"

#include "Terrain.h"

/**
 * Terrain implementation
 */


Terrain::Terrain(Grid * grilleProprietaire, int x, int y, TypeTerrain type)
	:m_grilleProprietaire(grilleProprietaire), m_x(x), m_y(y), m_type(type)
{
	switch (m_type)
	{
	case TypeTerrain::Eau:
		m_resource = RESSOURCES_EAU;
		break;
	case TypeTerrain::Terre:
		m_resource = RESSOURCES_TERRE;
		break;
	case TypeTerrain::Gazon:
		m_resource = RESSOURCES_GAZON;
		break;
	case TypeTerrain::Frontiere:
		m_resource = RESSOURCES_FRONTIERE;
		break;
	default:
		m_resource = RESSOURCES_FRONTIERE;
		break;
	}
}

/**
 * @return void
 */
void Terrain::reprendreRessources() {
	switch (m_type)
	{
	case TypeTerrain::Eau:
		if (m_grilleProprietaire->getTerrain(m_x + 1, m_y)->getType() == TypeTerrain::Eau ||
			m_grilleProprietaire->getTerrain(m_x - 1, m_y)->getType() == TypeTerrain::Eau ||
			m_grilleProprietaire->getTerrain(m_x, m_y + 1)->getType() == TypeTerrain::Eau ||
			m_grilleProprietaire->getTerrain(m_x, m_y - 1)->getType() == TypeTerrain::Eau)
		{
			m_resource = RESSOURCES_EAU;
		}
		break;
	case TypeTerrain::Terre:
		m_resource = RESSOURCES_TERRE;
		break;
	case TypeTerrain::Gazon:
		m_resource += RATE_GAZON;
		if (m_resource < RESSOURCES_GAZON)
		{
			m_resource = RESSOURCES_GAZON;
		}
		break;
	case TypeTerrain::Frontiere:
		m_resource = RESSOURCES_FRONTIERE;
		break;
	default:
		m_resource = RESSOURCES_FRONTIERE;
		break;
	}
}

void Terrain::perdreRessources(int nbRessources)
{
	m_resource -= nbRessources;

	if (m_resource < 0)
		m_resource = 0;
}

void Terrain::update()
{
	if (m_resource <= 0)
		m_type = TypeTerrain::Terre;

	this->reprendreRessources();
}

void Terrain::setType(TypeTerrain type)
{
	m_type = type;

	this->reprendreRessources();
}

Terrain::TypeTerrain Terrain::getType()
{
	return m_type;
}