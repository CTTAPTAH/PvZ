#pragma once
#include "GameObject.h"
#include "Manager.h"
#include "Message.h"
#include <iostream>
class Nut: public GameObject
{
private:


public:
	Nut(int idx_line, sf::Vector2f pos);
	Nut();
	~Nut();
	void draw(sf::RenderWindow& win);
	void update(double dt, sf::RenderWindow& win)override;
	void receiveMsg(Message* msg) override;
};

