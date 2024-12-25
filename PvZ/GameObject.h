#pragma once
#include <SFML/Graphics.hpp>

class Message;

struct Position {
	double x, y;
};

class GameObject
{
private:
	Position pos;
	int hp;
	sf::Texture* texture;
	int idx_line;
	int id;
public:
	GameObject();
	GameObject(const GameObject&);
	virtual ~GameObject();

	void ReceiveDamage();
	void UpdatePosition(double dt, double speed);
	void Animation(double dt);
	//void isLive();
	void Collision();

	//static int GetId();
	Position GetPosition();
	virtual void SendMsg(double dt);
	virtual void ReceiveMsg(Message* msg);
};