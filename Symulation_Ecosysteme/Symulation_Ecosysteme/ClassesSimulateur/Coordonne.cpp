/**
 * Project Untitled
 */
//#include "stdafx.h"

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
double Coordonne::getX() {
    return m_x;
}

/**
 * @return int
 */
double Coordonne::getY() {
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