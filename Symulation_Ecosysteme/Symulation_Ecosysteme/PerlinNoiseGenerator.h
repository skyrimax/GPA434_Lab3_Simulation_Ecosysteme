#pragma once

/**************************************************************
*Ce code est une implémentation modifiée de la fonction       *
*de bruit de Perlin. Elle a été tiré du code de Flafla2       *
*source : https://gist.github.com/Flafla2/f0260a861be0ebdeef76*
*Le code à été modifié pour le C++ ainsi que pour les         *
*normes de code de l'équipe. Le code original est écrit en C# *
**************************************************************/

// Librairies standart
#include <cmath>
#include <list>

class PerlinNoiseGenerator
{
public:
	PerlinNoiseGenerator(int seed=0, int repeat=-1);
	~PerlinNoiseGenerator();

	// Fonctions statique utilisée dans l'argoritme
	//---------------------------------------------------------------------
	// Fonction d'ammortissement, smoothing
	static double fade(double t);
	// Fonction d'interpolation linéaire
	static double lerp(double a, double b, double x);
	// Fonction retournant une valeure d'influence pour le point spécifié selon un hash
	static double grad(int hash, double x, double y, double z);
	// Version simplifiée de grad
	static double gradSimple(int hash, double x, double y, double z);

	// Fonction gérant la répétition
	int inc(int num);

	// Fonction de base du bruit de Perlin
	double perlin(double x, double y, double z);

	// Fonction de bruit de Perlin avec plusieurs échantillonnage
	double octavePerlin(double x, double y, double z, int octaves, double persistence);

private:

	// Table de hachage telle que définie par Ken Perlin
	// Tableau arrangé au hasard contenant tous les chiffres de 0 à 255
	/*static const*/ int m_permutation[256];

	// Table de hachage permutée 2 fois pour éviter le dépassement
	int m_p[512];

	// Nombre de répétitions
	int m_repeat;
};

// Table de hachage tiré d'internet
/*const int PerlinNoiseGenerator::m_permutation[256]= { 151,160,137,91,90,15,					// Hash lookup table as defined by Ken Perlin.  This is a randomly
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,	// arranged array of all numbers from 0-255 inclusive.
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};*/
