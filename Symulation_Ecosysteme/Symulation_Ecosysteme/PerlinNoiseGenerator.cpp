/**************************************************************
*Ce code est une implémentation modifiée de la fonction       *
*de bruit de Perlin. Elle a été tiré du code de Flafla2       *
*source : https://gist.github.com/Flafla2/f0260a861be0ebdeef76*
*Le code à été modifié pour le C++ ainsi que pour les         *
*normes de code de l'équipe. Le code original est écrit en C# *
**************************************************************/

#include "stdafx.h"

#include "PerlinNoiseGenerator.h"

PerlinNoiseGenerator::PerlinNoiseGenerator(int seed, int repeat )
	: m_repeat(repeat)
{
	std::vector<int> liste;

	srand(seed);

	for (int i = 0; i < 256; i++) {
		liste.push_back(i);
	}

	for (int i = 0; i < 256; i++) {
		int pos;

		pos = rand() % liste.size();

		m_permutation[i] = liste[pos];

		liste.erase(liste.begin() + pos);
	}

	for (int i = 0; i < 512; i++) {
		m_p[i] = m_permutation[i % 256];
	}
}

PerlinNoiseGenerator::~PerlinNoiseGenerator()
{
}

double PerlinNoiseGenerator::fade(double t)
{
	return t * t*t*(t*(t * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}

double PerlinNoiseGenerator::lerp(double a, double b, double x)
{
	return a + x * (b - a);
}

// Pris directement d'internet
double PerlinNoiseGenerator::grad(int hash, double x, double y, double z)
{
	int h = hash & 15;									// Take the hashed value and take the first 4 bits of it (15 == 0b1111)
	double u = h < 8 /* 0b1000 */ ? x : y;				// If the most significant bit (MSB) of the hash is 0 then set u = x.  Otherwise y.

	double v;											// In Ken Perlin's original implementation this was another conditional operator (?:).  I
														// expanded it for readability.

	if (h < 4 /* 0b0100 */)								// If the first and second significant bits are 0 set v = y
		v = y;
	else if (h == 12 /* 0b1100 */ || h == 14 /* 0b1110*/)// If the first and second significant bits are 1 set v = x
		v = x;
	else 												// If the first and second significant bits are not equal (0/1, 1/0) set v = z
		v = z;

	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v); // Use the last 2 bits to decide if u and v are positive or negative.  Then return their addition.
}

double PerlinNoiseGenerator::gradSimple(int hash, double x, double y, double z)
{
	switch (hash & 0xF)
	{
	case 0x0: return  x + y;
	case 0x1: return -x + y;
	case 0x2: return  x - y;
	case 0x3: return -x - y;
	case 0x4: return  x + z;
	case 0x5: return -x + z;
	case 0x6: return  x - z;
	case 0x7: return -x - z;
	case 0x8: return  y + z;
	case 0x9: return -y + z;
	case 0xA: return  y - z;
	case 0xB: return -y - z;
	case 0xC: return  y + x;
	case 0xD: return -y + z;
	case 0xE: return  y - x;
	case 0xF: return -y - z;
	default: return 0.0; // N'arrive jamais
	}
}

int PerlinNoiseGenerator::inc(int num)
{
	num++;
	if (m_repeat > 0) num %= m_repeat;

	return num;
}

double PerlinNoiseGenerator::perlin(double x, double y, double z)
{
	/*if (m_repeat > 0) {
		x = x % m_repeat;
		y = y % m_repeat;
		z = z % m_repeat;
	}*/

	/*// Pas certain de ça-------
	int xi = floor(x);
	int yi = floor(y);
	int zi = floor(z);
	double xf = xi + 1;
	double yf = yi + 1;
	double zf = zi + 1;
	//-------------------------*/
	// Version trouvée en ligne
	int xi = (int)x & 255;
	int yi = (int)y & 255;
	int zi = (int)z & 255;
	double xf = x - (int)x;
	double yf = y - (int)y;
	double zf = z - (int)z;
	//-------------------------

	double u = PerlinNoiseGenerator::fade(xf);
	double v = PerlinNoiseGenerator::fade(yf);
	double w = PerlinNoiseGenerator::fade(zf);

	int aaa, aba, aab, abb, baa, bba, bab, bbb;
	aaa = m_p[m_p[m_p[xi] + yi] + zi];
	aba = m_p[m_p[m_p[xi] + PerlinNoiseGenerator::inc(yi)] + zi];
	aab = m_p[m_p[m_p[xi] + yi] + PerlinNoiseGenerator::inc(zi)];
	abb = m_p[m_p[m_p[xi] + PerlinNoiseGenerator::inc(yi)] + PerlinNoiseGenerator::inc(zi)];
	baa = m_p[m_p[m_p[PerlinNoiseGenerator::inc(xi)] + yi] + zi];
	bba = m_p[m_p[m_p[PerlinNoiseGenerator::inc(xi)] + PerlinNoiseGenerator::inc(yi)] + zi];
	bab = m_p[m_p[m_p[PerlinNoiseGenerator::inc(xi)] + yi] + PerlinNoiseGenerator::inc(zi)];
	bbb = m_p[m_p[m_p[PerlinNoiseGenerator::inc(xi)] + PerlinNoiseGenerator::inc(yi)] + PerlinNoiseGenerator::inc(zi)];

	double x1, x2, y1, y2;
	/*x1 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::grad(aaa, xf, yf, zf),
		PerlinNoiseGenerator::grad(baa, xf - 1, yf, zf),
		u);
	x2 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::grad(aba, xf, yf - 1, zf),
		PerlinNoiseGenerator::grad(bba, xf - 1, yf - 1, zf),
		u);*/
	x1 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::gradSimple(aaa, xf, yf, zf),
		PerlinNoiseGenerator::gradSimple(baa, xf - 1, yf, zf),
		u);
	x2 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::gradSimple(aba, xf, yf - 1, zf),
		PerlinNoiseGenerator::gradSimple(bba, xf - 1, yf - 1, zf),
		u);
	y1 = PerlinNoiseGenerator::lerp(x1, x2, v);

	/*x1 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::grad(aab, xf, yf, zf - 1),
		PerlinNoiseGenerator::grad(bab, xf - 1, yf, zf - 1),
		u);
	x2 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::grad(abb, xf, yf - 1, zf - 1),
		PerlinNoiseGenerator::grad(baa, xf - 1, yf - 1, zf - 1),
		u);*/
	x1 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::gradSimple(aab, xf, yf, zf - 1),
		PerlinNoiseGenerator::gradSimple(bab, xf - 1, yf, zf - 1),
		u);
	x2 = PerlinNoiseGenerator::lerp(PerlinNoiseGenerator::gradSimple(abb, xf, yf - 1, zf - 1),
		PerlinNoiseGenerator::gradSimple(baa, xf - 1, yf - 1, zf - 1),
		u);
	y2 = PerlinNoiseGenerator::lerp(x1, x2, v);

	return (PerlinNoiseGenerator::lerp(y1, y2, w) + 1) / 2;
}

double PerlinNoiseGenerator::octavePerlin(double x, double y, double z, int octaves, double persistence)
{
	double total = 0;
	double frequency = 1;
	double amplitude = 1;
	double maxValue = 0;
	for (int i = 0; i < octaves; i++) {
		total += this->perlin(x*frequency, y*frequency, z*frequency)*amplitude;

		maxValue += amplitude;
		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}
