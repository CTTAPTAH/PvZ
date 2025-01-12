#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
private:
	double speed = 300;
public:
	Projectile();
	Projectile(Position pos_, sf::IntRect rect_, sf::Color color);
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void update(double dt, sf::RenderWindow& win);
	void sendMsg();
	void receiveMsg();
};

