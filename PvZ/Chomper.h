#pragma once

#include "GameObject.h"
#include "Manager.h"
#include "Message.h"
#include <iostream>
class Chomper : public GameObject
{
private:
	double time_to_chew_zombie = 10;

	double chewing_zombie_timer;

	GameObject* victim = nullptr;

	bool isEating = false;
public:
	Chomper();
	Chomper(int idx_line, sf::Vector2f pos);
	~Chomper();

	void draw(sf::RenderWindow& win);
	void receiveMsg(Message* msg) override;
	void update(double dt, sf::RenderWindow& win) override;
	void EatingZombie1(double dt);
	void EatingZombie(double dt, GameObject* object);
	GameObject* CollisionWithZombie();
	bool getIsEating();
};


