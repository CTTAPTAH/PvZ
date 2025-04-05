#pragma once
#include <iostream>
#include "GameObject.h"
#include "Manager.h"
#include <cmath>

#define IDLE_SUN 0
#define MOVE_SUN 1

class Sun :public GameObject
{
private:

	int current_motion = MOVE_SUN;
	static int collected_sun;
	int velocity_x = 100;
	double velocity_y;
	double start_pos_y;
	double ground_pos_y;
	bool firstMove = true;

	bool touch = false;

	static sf::Texture* texture;
	sf::Sprite sprite;

public:
	Sun(int pos_x, int pos_y, int index_line_);
	Sun();
	~Sun();
	void move_from_sunflower(double dt);
	void draw(sf::RenderWindow& win);
	void update(double dt, sf::RenderWindow& win) override;
	void receiveMsg(Message* msg) override;
	void CollisionWithCursor(sf::RenderWindow& win);
	void TextureCollisionWithCursor(sf::RenderWindow& win, double dt);
};

