/*
Cette classe permet de gérer tous ce qui est en lien avec les coordonnées.
Nos coordonnées sont en X et Y (en double), d'ailleurs le plan cartésien de Qt
à l'axe des Y vers le bas de l'écran, celui de l'axe des X est orienté vers la droite.
Donc, cette classe nous permet de renvoyer les coordonnées de nos animaux et plantes.
*/
#include "stdafx.h"

#include "Coordonne.h"

/**
 * Coordonne implementation
 */


Coordonne::Coordonne(double x, double y)
	: m_x(x), m_y(y)
{
}

/**
 * @return double
 */
const double& Coordonne::getX() const {
    return m_x;
}

/**
 * @return int
 */
const double& Coordonne::getY() const {
    return m_y;
}

/**
 * @return void
 */
void Coordonne::setX(double x) {
	m_x = x;
}

/**
 * @return void
 */
void Coordonne::setY(double y) {
	m_y = y;
}

/**
 * @return void
 */
void Coordonne::moveX(double deltaX) {
	m_x += deltaX;
}

/**
 * @return void
 */
void Coordonne::moveY(double deltaY) {
	m_y += deltaY;
}