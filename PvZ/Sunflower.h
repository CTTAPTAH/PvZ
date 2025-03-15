#pragma once
#include "GameObject.h"
#include "Manager.h"
#include "Sun.h"
#include<iostream>


class Sunflower: public GameObject
{
private:
	int time_to_reaper_sun;
	double current_time = 0;
public:
	Sunflower();
	Sunflower(int index_line_, TypeObject  type_, int pos_x, int pos_y);
	~Sunflower();
	void dropsun(double dt);
	void draw(sf::RenderWindow& win);
	void ReceiveMsg(Message* msg) override;
	void update(double dt, sf::RenderWindow& win) override;
	void setRect(sf::IntRect rect_);
	int random(int a, int b);
};

