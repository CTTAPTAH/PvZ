#pragma once
#include "Zombie.h"

class ConusZombie : public Zombie
{
private:
	bool isHavePaper = true;
public:
	// �������, �������
	ConusZombie(int idx_line);

	// ������b
	virtual ~ConusZombie() = default;
	void receiveMsg(Message* msg) override;
};

