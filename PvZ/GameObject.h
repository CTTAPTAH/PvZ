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
	int win_width = 800, win_height = 600; // в config
	Position pos; // временно не нужен, т.к. имеется rect
	int hp;
	sf::Texture* texture; // временно не нужен, т.к. имеется rect и color
	int idx_line;
	TypeObject type; // Скорее всего не понадобится. Всё реализовано в update
public:
	GameObject();
	GameObject(int idx_line_, TypeObject type);
	GameObject(const GameObject&);
	virtual ~GameObject();

	void ReceiveDamage();
	virtual void update(double dt, sf::RenderWindow& win);
	void UpdatePosition(double dt, double speed); // переименовать на move и скорее всего убрать
	void Animation(double dt);
	//void isLive();
	void Collision();

	//static int GetId();
	Position getPosition();
	virtual void draw(sf::RenderWindow& win);
	virtual void setPosition(Position pos_);
	virtual void SendMsg(double dt);
	virtual void ReceiveMsg(Message* msg);
};