#pragma once
#include "Manager.h"
#include "GameObject.h"
#include "Message.h"
#include "Zombie.h"

class PeaProjectile : public GameObject
{
protected:
	double speed;
	double damage;
	bool is_dead;
public:
	// конструкторы, деструкторы
	PeaProjectile();
	PeaProjectile(sf::Vector2f vect, int idx_line_, double damage);
	~PeaProjectile() = default;

	// методы
	void update(double dt, sf::RenderWindow& win)override;
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void checkOutOfBounds();
	virtual void collisionWithZombies();
	void receiveMsg(Message* msg) override;

	//геттеры, сеттеры
	void setRect(sf::FloatRect rect_);
};