#pragma once

#include "Manager.h"
#include "GameObject.h"
#include "Projectile.h"

class Peashooter : public GameObject
{
protected:
	bool shooting = false;
	const int amount_hp = 10; // â config
	const double damage = 1; // â config
	const double time_reload = 2; // â config
	double reload;
public:
	Peashooter(int idx_line_, TypeObject type_);
	Peashooter();

	void isShooting(double dt);
	void update(double dt, sf::RenderWindow& win) override;
	void setPosition(Position pos_);
	void setRect(sf::IntRect rect_);
	void setColor(sf::Color color_);
};