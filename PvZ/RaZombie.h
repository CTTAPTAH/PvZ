#pragma once
#include "Zombie.h"

class RaZombie : public Zombie
{
private:
	bool isTakeSuns = false;
	Sun* currentSun = nullptr;
	bool onMap = false;

	bool WasTaken=false;

	static std::list<RaZombie*> waiting_list;

public:
	RaZombie(int idx_line, int frame_w, int frame_h);
	virtual ~RaZombie();
	void MagnetSun(double dt);
	void move(double dt) override;
	void update(double dt, sf::RenderWindow& win) override;
	void setIsTakeSuns(bool isHappend);
	void currentSunNullable(RaZombie* owner);
	bool getOnMap();
};

