/*
Le Grid c'est lui qui va générer les cases de notre terrain, cette génération
est faite à l'aide du Perlin Noise (Voir PerlinNoiseGenerator.cpp). Une case peut
être soit de la terre, de l'eau, du gazon, une plante ou une frontière (limite 
de notre environnement).
*/
#include "stdafx.h"

#include "Grid.h"
#include "PerlinNoiseGenerator.h"
#include "Environement.h"

/**
 * Grid implementation
 */
Grid::Grid(Environnement* environnement)
	: m_environnementProprietaire(environnement)
{

	PerlinNoiseGenerator terrainGenerator;

	Terrain::TypeTerrain type;

	for (int i = 0; i < LARGEUR_GRILLE; i++) {
		for (int j = 0; j < HAUTEUR_GRILLE; j++)
		{
			if (i == 0 ||
				i == LARGEUR_GRILLE - 1 ||
				j == 0 ||
				j == HAUTEUR_GRILLE - 1)
			{
				type = Terrain::TypeTerrain::Frontiere;
			}
			else
			{
				double noise;

				noise = terrainGenerator.octavePerlin(i*10.0/LARGEUR_GRILLE, j*10.0/HAUTEUR_GRILLE, 0.0, OCTAVES, PERSISTENCE);

				if (noise < THRESHOLD_EAU)
					type = Terrain::TypeTerrain::Eau;
				else if (noise < THRESHOLD_TERRE)
					type = Terrain::TypeTerrain::Terre;
				else if (noise < THRESHOLD_GAZON)
					type = Terrain::TypeTerrain::Gazon;
				else if (noise < THRESHOLD_PLANTE) {
					m_environnementProprietaire->addPlante(new Plante(m_environnementProprietaire, /*Ajouter non de plante ici*/ "Plante",
						/*Ajouter hp ici*/ 100, /*Ajouter energy*/3000, /*Ajouter age adulte*/ 300, /*Ajouter age max*/27000,
						i, j, /*Ajouter temps reproduction*/ 300));

					type = Terrain::TypeTerrain::Gazon;
				}
			}

			m_grid[i][j] = new Terrain(this, i, j, type);

			m_environnementProprietaire->addItem(m_grid[i][j]);
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < LARGEUR_GRILLE; i++) {
		for (int j = 0; j < HAUTEUR_GRILLE; j++) {
			m_environnementProprietaire->removeItem(m_grid[i][j]);

			delete m_grid[i][j];
		}
	}
}


void Grid::updateTerrain() {
	for (int i = 0; i < LARGEUR_GRILLE; i++) {
		for (int j = 0; j < HAUTEUR_GRILLE; j++) {
			m_grid[i][j]->update();
		}
	}
}

Terrain * Grid::getTerrain(int x, int y)
{
	return m_grid[x][y];
}
