#pragma once
// Librairies standart
#include <cmath>

class PerlinNoiseGenerator
{
public:
	PerlinNoiseGenerator(int repeat=-1);
	~PerlinNoiseGenerator();

	// Fonctions statique utilisée dans l'argoritme
	//---------------------------------------------------------------------
	// Fonction d'ammortissement, smoothing
	static double fade(double t);
	// Fonction d'interpolation linéaire
	static double larp(double a, double b, double x);
	// Fonction retournant une valeure d'influence pour le point spécifié selon un hash
	static double grad(int hash, double x, double y, double z);

	// Fonction gérant la répétition
	int inc(int num);

	// Fonction de base du bruit de Perlin
	double perlin(double x, double y, double z);

	// Fonction de bruit de Perlin avec plusieurs échantillonnage
	double octavePerlin(double x, double y, double z, int octaves, double persistence);

private:

	// Table de hachage telle que définie par Ken Perlin
	// Tableau arrangé au hasard contenant tous les chiffres de 0 à 255
	static const int m_permutation[256];

	// Table de hachage permutée 2 fois pour éviter le dépassement
	int m_p[512];

	// Nombre de répétitions
	int m_repeat;
};
