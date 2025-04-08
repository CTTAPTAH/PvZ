#pragma once
#include "Zombie.h"

class ConusZombie : public Zombie
{
private:
	bool isHavePaper = true;
public:
	// геттеры, сеттеры
	ConusZombie(int idx_line);

	// методыb
	virtual ~ConusZombie() = default;
	void receiveMsg(Message* msg) override;
};

