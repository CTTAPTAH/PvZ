#pragma once
#include "Manager.h"
#include "GameObject.h"
#include "Message.h"
#include "Zombie.h"

class PeaProjectile : public GameObject
{
private:
	double speed;
	double damage;
	bool is_dead;
public:
	// конструкторы, деструкторы
	PeaProjectile();
	PeaProjectile(sf::IntRect rect_, int idx_line_, double damage);
	~PeaProjectile() = default;

	// методы
	void update(double dt, sf::RenderWindow& win);
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void checkOutOfBounds();
	void collisionWithZombies();
	void receiveMsg(Message* msg) override;

	//геттеры, сеттеры
	void setRect(sf::IntRect rect_);
};