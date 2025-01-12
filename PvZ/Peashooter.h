#pragma once

#include "Manager.h"
#include "GameObject.h"
#include "Projectile.h"

class Peashooter : public GameObject
{
protected:
	const double damage = 2;
	const double time_reload = 3;
	double reload;
public:
	Peashooter(Position pos_, int hp_, int idx_line_, TypeObject type_);
	Peashooter();

	void isShooting(double dt);
	void Update(double dt);
	void setPosition(Position pos_);
	void setRect(sf::IntRect rect_);
	void setColor(sf::Color color_);
};

