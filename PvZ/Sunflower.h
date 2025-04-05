#pragma once
#include "GameObject.h"
#include "Manager.h"
#include "Sun.h"
#include<iostream>


class Sunflower : public GameObject
{
private:

	//sf::Color color; // Ќикита добавил, потому что больше не наследуем
	int time_to_reaper_sun;
	double current_time = 0;
public:
	Sunflower();
	Sunflower(sf::Vector2i pos, int index_line_);
	~Sunflower();
	void dropsun(double dt);
	void draw(sf::RenderWindow& win);
	void receiveMsg(Message* msg) override;
	void update(double dt, sf::RenderWindow& win) override;
	void setRect(sf::IntRect rect_);
};

