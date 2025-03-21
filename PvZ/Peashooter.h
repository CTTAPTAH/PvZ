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
	// ������������, �����������
	Peashooter();
	Peashooter(sf::Vector2i pos, int idx_line_);
	~Peashooter() = default;

	// ������
	void update(double dt, sf::RenderWindow& win) override;
	void isShooting(double dt);
	void draw(sf::RenderWindow& win);
	void receiveMsg(Message* msg) override;

	// �������, �������
	void setRect(sf::IntRect rect_);
};