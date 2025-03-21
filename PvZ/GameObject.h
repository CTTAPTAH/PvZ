#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class Message;

enum class TypeObject {
	PLANT, ZOMBIE, PROJECTILE, UNDEFINED
};

class GameObject
{
protected:
	Animation animation;
	sf::IntRect rect;
	int hp;
	int idx_line;
	TypeObject type;
public:
	// ������������, �����������
	GameObject();
	GameObject(Animation animation_, sf::IntRect rect_,
		int hp_, int idx_line_,
		TypeObject type_);
	GameObject(const GameObject&) = default;
	virtual ~GameObject() = default;

	// ������
	// ����� ����������� ������
	virtual void receiveMsg(Message* msg) = 0;
	virtual void update(double dt, sf::RenderWindow& win) = 0;

	// �������, �������
	Animation getAnimetion() const;
	sf::IntRect getRect() const;
	int getHp() const;
	int getIdxLine() const;
	TypeObject getType() const;
};