/**
 * Project Untitled
 */


#ifndef _CARNIVORE_H
#define _CARNIVORE_H

#include "Animal.h"



class Carnivore: public Animal {
public: 

	// Constructeur
	Carnivore() = default;
	Carnivore(Environnement* environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax,
		double x, double y, double vitesse, double sprint, Sex sex, int nbProgenituresMin, int nbProgenituresMax,
		Animal * mere, Meute * meute, int timerMort, int tempsGestation, int tempsReproduction, std::list<std::string>cible);

	// Fonctions membres des carnivores
	bool isCharognard();

	// Fonctions membre virtuelles héritées de QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	// Fonctions membre virtuelles héritées de Vivant
	virtual void replenishEnergy() override;
	virtual void seekEnergy() override;
	virtual void simulation() override;

	// Fonctions membres virtuelles héritées de Animal
	virtual void chooseTarget() override;
	virtual void chooseTarget(Vivant* target) override;
	virtual void resetTarget() override;
	virtual void trackTarget() override;
	virtual void removeFromTarget() override;
	virtual void chooseMate() override;
	virtual void trackMate() override;
	virtual void accoucher() override;

	// Accesseur virtuel hérité de Animal
	virtual Vivant* getTarget() override;

protected:
    Vivant* m_proie;
    bool m_isCharognard;

private:
	//Ajouté par Fred, la forme des carnivores
	QPolygonF mshape;
	//Ajouté par Fred, couleur des carnivores
	QColor sCarnivoreBackgoundColor;
};

#endif //_CARNIVORE_H
