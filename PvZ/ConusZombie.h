#pragma once
#include "Zombie.h"

class ConusZombie : public Zombie
{
public:
	// ������������, ������������
	ConusZombie(int idx_line);
	virtual ~ConusZombie() = default;

	// ������
	void receiveMsg(Message* msg) override;
};

