#pragma once
#include "Peashooter.h"
#include "SnowPeaProjectile.h"

class SnowPeashooter : public Peashooter
{
public:
	SnowPeashooter(int idx_line, sf::Vector2i pos);
	~SnowPeashooter();

	void isShooting(double dt)override;
};

