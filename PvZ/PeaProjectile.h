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
	// ������������, �����������
	PeaProjectile();
	PeaProjectile(sf::IntRect rect_, int idx_line_, double damage);
	~PeaProjectile() = default;

	// ������
	void update(double dt, sf::RenderWindow& win);
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void checkOutOfBounds();
	void collisionWithZombies();
	void receiveMsg(Message* msg) override;

	//�������, �������
	void setRect(sf::IntRect rect_);
};