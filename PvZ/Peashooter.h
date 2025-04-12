#pragma once

#include "Manager.h"
#include "GameObject.h"
#include "PeaProjectile.h"
#include "Message.h"

class Peashooter : public GameObject
{
protected:
	bool is_shooting;
	double damage;
	double time_reload;
	double reload;


public:
	// конструкторы, деструкторы
	Peashooter();
	Peashooter(sf::Vector2f pos, int idx_line_);
	~Peashooter() = default;

	// методы
	void update(double dt, sf::RenderWindow& win) override;
	void draw(sf::RenderWindow& win) override;
	void receiveMsg(Message* msg) override;
	virtual void isShooting(double dt);

	// геттеры, сеттеры
};