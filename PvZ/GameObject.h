#pragma once
#include <SFML/Graphics.hpp>
class Message;

enum class TypeObject {
	UNDEFINED, PEASHOOTER
};
struct Position {
	double x = 0, y = 0;
};

class GameObject
{
protected:
	// временно место текстуры
	sf::IntRect rect;
	sf::Color color;
	// То, что было
	Position pos;
	int hp;
	sf::Texture* texture;
	int idx_line;
	TypeObject type;
public:
	GameObject();
	GameObject(Position pos_, int hp_, int idx_line_, TypeObject type);
	GameObject(const GameObject&);
	virtual ~GameObject();

	void ReceiveDamage();
	void Update();
	void UpdatePosition(double dt, double speed);
	void Animation(double dt);
	//void isLive();
	void Collision();

	//static int GetId();
	Position GetPosition();
	virtual void draw(sf::RenderWindow& win);
	virtual void setPosition(Position pos_);
	virtual void SendMsg(double dt);
	virtual void ReceiveMsg(Message* msg);
};