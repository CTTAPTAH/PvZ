#pragma once
#include "GameObject.h"
#include "Manager.h"
#include <iostream>
class Car:public GameObject
{
private:
	double velocity_x = 400;
	bool touch = false;

	static sf::Texture* texture;
	sf::Sprite sprite;
public:
	Car();
	Car(int index_line_, TypeObject type, int w_cell, int h_cell);
	~Car();
	void update(double dt, sf::RenderWindow& win)override;
	void ReceiveMsg(Message* msg)override;
	void draw(sf::RenderWindow& win);
	void move(double dt);
	void CollisionWithZombie(double dt);
	void checkboarders();
};

