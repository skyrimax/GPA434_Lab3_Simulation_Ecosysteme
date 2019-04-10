/**
 * Project Untitled
 */


#ifndef _HERBIVORE_H
#define _HERBIVORE_H

#include "Animal.h"
#include "Plante.h"

 // Déclaration enticipée
class Plante;

class Herbivore: public Animal {
public:

	// Constructeur
	Herbivore() = default;
	Herbivore(Environnement* environnement, std::string espece, int hp,
		int energy, int ageAdulte, int ageMax, double x, double y,
		double vitesse, double sprint, Sex sex,
		int nbProgenituresMin, int nbProgenituresMax,
		Animal* mere, Meute* meute,
		int timerMort, int tempsGestation, int tempsReproduction,
		std::list<std::string> cible);

	// Fonctions membres virtuelles héritées de QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	// Fonctions membres virtuelles héritées de Vivant
	virtual void replenishEnergy() override;
	virtual void seekEnergy() override;
	virtual void simulation() override;

	// Fonctions membres virtuelles héritées de Animal
	virtual void chooseTarget() override;
	virtual void chooseTarget(Vivant* target) override;
	virtual void resetTarget() override;
	virtual void trackTarget() override;
	virtual void chooseMate() override;
	virtual void trackMate() override;
	virtual void accoucher() override;

protected: 
    Plante* m_plante;
};

#endif //_HERBIVORE_H