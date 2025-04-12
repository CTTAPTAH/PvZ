#pragma once
#include "PeaProjectile.h"
class SnowPeaProjectile : public PeaProjectile
{
public:
	SnowPeaProjectile(sf::Vector2f vect, int idx_line_, double damage_);
	~SnowPeaProjectile();
	void collisionWithZombies()override;
};

