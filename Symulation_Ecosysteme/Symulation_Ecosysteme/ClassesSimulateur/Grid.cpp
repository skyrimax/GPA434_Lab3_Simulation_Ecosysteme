/**
 * Project Untitled
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
					m_environnementProprietaire->addPlante(new Plante(m_environnementProprietaire, /*Ajouter non de plante ici*/ "Arbre",
						/*Ajouter hp ici*/ 1, /*Ajouter energy*/1, /*Ajouter age adulte*/ 10, /*Ajouter age max*/100,
						i, j, /*Ajouter temps reproduction*/ 300));

					type = Terrain::TypeTerrain::Gazon;
				}
			}

			m_grid[i][j] = new Terrain(this, i, j, type);
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
