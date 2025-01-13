#pragma once
#include "Manager.h"
#include "GameObject.h"
#include "Message.h"

class Projectile : public GameObject
{
private:
	double speed = 300;
public:
	Projectile();
	Projectile(sf::IntRect rect_, sf::Color color);
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void update(double dt, sf::RenderWindow& win);
	void collision(); // не забыть добавить проверку с зомби
	void sendMsg(); // ¬ќ«ћќ∆Ќќ придЄтс€ убрать
	void receiveMsg(); // ¬ќ«ћќ∆Ќќ придЄтс€ убрать
};

