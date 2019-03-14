/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Grid.h"
#include "PerlinNoiseGenerator.h"

/**
 * Grid implementation
 */
Grid::Grid()
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
				int noise;

				noise = terrainGenerator.octavePerlin(i, j, 0, OCTAVES, PERSISTENCE);

				if (noise < THRESHOLD_EAU)
					type = Terrain::TypeTerrain::Eau;
				else if (noise < THRESHOLD_TERRE)
					type = Terrain::TypeTerrain::Terre;
				else if (noise < THRESHOLD_GAZON)
					type = Terrain::TypeTerrain::Gazon;
				else if (noise < THRESHOLD_PLANTE) {
					m_environnementProprietaire->addPlante(Plante());

					type = Terrain::TypeTerrain::Gazon;
				}
			}

			m_grid[i][j] = new Terrain(this, i, j, type);
		}
	}
}


/**
 * @return void
 */
void Grid::updateTerrain() {
	for (int i = 0; i < LARGEUR_GRILLE; i++) {
		for (int j = 0; i < HAUTEUR_GRILLE; i++) {
			m_grid[i][j]->update();
		}
	}
}

Terrain * Grid::getTerrain(int x, int y)
{
	return m_grid[x][y];
}
