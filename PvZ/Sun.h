#pragma once
#include <iostream>
#include "GameObject.h"
#include "Manager.h"
#include <cmath>

#define IDLE_SUN 0
#define MOVE_SUN 1

class RaZombie;

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

	double variable_speed;
	double zombie_timer = 0;

	bool onGround = false;
	bool SunTrappedByZombie = false;

	bool touch = false;

	RaZombie* owner_zombie = nullptr;

	
public:
	Sun(float pos_x, float pos_y, int index_line_);
	Sun();
	~Sun();
	void move_from_sunflower(double dt);
	void draw(sf::RenderWindow& win);
	void update(double dt, sf::RenderWindow& win) override;
	void receiveMsg(Message* msg) override;
	void CollisionWithCursor(sf::RenderWindow& win);
	void TextureCollisionWithCursor(sf::RenderWindow& win, double dt);
	void SetSunTrapped(bool isHappend);
	void SetOwnerSun(RaZombie* owner);
	bool GetSunTrapped();
	void MoveToZombie(double dt);
	void checkTimer();
	bool getOnGround();
	bool isTouched() const;
};

