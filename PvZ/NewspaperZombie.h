#pragma once
#include "Zombie.h"
class NewspaperZombie: public Zombie
{
private:
	bool isHavePaper = true;
public:
	NewspaperZombie(int idx_line, int frame_w, int frame_h);
	virtual ~NewspaperZombie();
	void receiveMsg(Message* msg) override;
};

