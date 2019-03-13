#pragma once
// Librairies standart
#include <cmath>

class PerlinNoiseGenerator
{
public:
	PerlinNoiseGenerator(int repeat=-1);
	~PerlinNoiseGenerator();

	// Fonctions statique utilis�e dans l'argoritme
	//---------------------------------------------------------------------
	// Fonction d'ammortissement, smoothing
	static double fade(double t);
	// Fonction d'interpolation lin�aire
	static double larp(double a, double b, double x);
	// Fonction retournant une valeure d'influence pour le point sp�cifi� selon un hash
	static double grad(int hash, double x, double y, double z);

	// Fonction g�rant la r�p�tition
	int inc(int num);

	// Fonction de base du bruit de Perlin
	double perlin(double x, double y, double z);

	// Fonction de bruit de Perlin avec plusieurs �chantillonnage
	double octavePerlin(double x, double y, double z, int octaves, double persistence);

private:

	// Table de hachage telle que d�finie par Ken Perlin
	// Tableau arrang� au hasard contenant tous les chiffres de 0 � 255
	static const int m_permutation[256];

	// Table de hachage permut�e 2 fois pour �viter le d�passement
	int m_p[512];

	// Nombre de r�p�titions
	int m_repeat;
};
