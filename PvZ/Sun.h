#pragma once
#include <iostream>
#include "GameObject.h"
#include "Manager.h"
#include <cmath>
class Sun:public GameObject
{
private:
	static int collected_sun;
	int velocity_x = 100;
	double velocity_y;
	double start_pos_y;
	double ground_pos_y;
	bool firstMove = true;

	static sf::Texture* texture;
	sf::Sprite sprite;

public:
	Sun(int pos_x, int pos_y);
	Sun();
	~Sun();
	void move(double dt);
	void draw(sf::RenderWindow& win);
	void update(double dt, sf::RenderWindow& win)override;
	void ReceiveMsg(Message* msg)override;
	void CollisionWithCursor(sf::RenderWindow& win);
	void TextureCollisionWithCursor(sf::RenderWindow& win);
};

