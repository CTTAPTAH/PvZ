#pragma once
#include "Zombie.h"

class DiscoZombie : public Zombie
{
private:
	bool hasSpawned;
public:
	// конструкторы, декструкторы
	DiscoZombie(int idx_line);
	virtual ~DiscoZombie() = default;

	// методы
	void move(double dt) override;
};

