#pragma once
#include "Zombie.h"

class DiscoZombie : public Zombie
{
private:
	bool hasSpawned;
public:
	// ������������, ������������
	DiscoZombie(int idx_line);
	virtual ~DiscoZombie() = default;

	// ������
	void move(double dt) override;
};

