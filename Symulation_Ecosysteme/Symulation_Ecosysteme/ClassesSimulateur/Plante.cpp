/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Plante.h"
#include "Herbivore.h"

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

void Plante::reproduction()
{
}

void Plante::simulation()
{
}

void Plante::dying()
{
}

bool Plante::isDead()
{
	return false;
}
