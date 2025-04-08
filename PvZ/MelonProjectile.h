#pragma once
#include "Manager.h"
#include "Message.h"

class MelonProjectile : public GameObject
{
private:
	sf::Vector2f pos;
	double vx;
	double vy;
	double damage;
public:
	// конструкторы, деструкторы
	MelonProjectile();
	MelonProjectile(sf::Vector2i pos_, int idx_line_, double vx_);
	~MelonProjectile() = default;

	// методы
	void update(double dt, sf::RenderWindow& win)override;
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void checkOutOfBounds();
	void collisionWithZombies();
	void receiveMsg(Message* msg) override;

	//геттеры, сеттеры
};