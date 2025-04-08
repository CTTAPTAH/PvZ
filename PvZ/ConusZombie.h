#pragma once
#include "Zombie.h"

class ConusZombie : public Zombie
{
public:
	// конструкторы, декструкторы
	ConusZombie(int idx_line);
	virtual ~ConusZombie() = default;

	// методы
	void receiveMsg(Message* msg) override;
};

