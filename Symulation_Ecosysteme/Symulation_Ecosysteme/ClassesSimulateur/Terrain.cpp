/**
 * Project Untitled
 */

#include "stdafx.h"

#include "Terrain.h"
#include "Grid.h"
#include <QPainter>


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

	setPos(x, y);

	
/*	Ajout par Fred
Création d'un rectangle de 1 par 1 positioné à (x,y)
	qui représente le terrain à un point*/
	mshape.setRect(x, y, 5, 5);

	sWaterBackgoundColor.setRgb(0,0,75);//bleu
	sGrassBackgoundColor.setRgb(0, 75, 0);//Vert
	sEarthBackgoundColor.setRgb(50, 25, 0);//brun
	sFrontierBackgoundColor.setRgb(0, 0, 0);//noir
}

QRectF Terrain::boundingRect() const
{
	//Ajouté par Fred
	return QRectF(m_x, m_y, 1, 1);
}

void Terrain::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ajout par Fred
	switch (m_type)
	{
	case Terrain::TypeTerrain::Eau:
		painter->setPen(Qt::NoPen);
		painter->setBrush(sWaterBackgoundColor);
		painter->drawRect(mshape);
		break;
	case Terrain::TypeTerrain::Terre:
		painter->setPen(Qt::NoPen);
		painter->setBrush(sEarthBackgoundColor);
		painter->drawRect(mshape);
		break;
	case Terrain::TypeTerrain::Gazon:
		painter->setPen(Qt::NoPen);
		painter->setBrush(sGrassBackgoundColor);
		painter->drawRect(mshape);
		break;
	case Terrain::TypeTerrain::Frontiere:
		painter->setPen(Qt::NoPen);
		painter->setBrush(sFrontierBackgoundColor);
		painter->drawRect(mshape);
		break;
	default:
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

void Terrain::gainRessources(int nbRessources)
{
	m_resource += nbRessources;
	switch (m_type)
	{
	case Terrain::TypeTerrain::Eau:
		if (m_resource > RESSOURCES_EAU)
			m_resource = RESSOURCES_EAU;
		break;
	case Terrain::TypeTerrain::Terre:
		if (m_resource > RESSOURCES_TERRE)
			m_resource = RESSOURCES_TERRE;
		break;
	case Terrain::TypeTerrain::Gazon:
		if (m_resource > RESSOURCES_GAZON)
			m_resource = RESSOURCES_GAZON;
		break;
	case Terrain::TypeTerrain::Frontiere:
		if (m_resource > RESSOURCES_FRONTIERE)
			m_resource = RESSOURCES_FRONTIERE;
		break;
	default:
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

bool Terrain::hasPlante()
{
	return m_hasPlante;
}

void Terrain::setType(TypeTerrain type)
{
	m_type = type;

	this->reprendreRessources();
}

void Terrain::setHasPlante(bool hasPlante)
{
	m_hasPlante = hasPlante;
}

Terrain::TypeTerrain Terrain::getType()
{
	return m_type;
}

int Terrain::getRessources()
{
	return m_resource;
}
