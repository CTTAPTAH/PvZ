#include "GameObject.h"

// конструкторы, деструкторы
GameObject::GameObject()
	: animation(),
	rect{ 0, 0, 0, 0 },
	hp(0),
	idx_line(0),
	type(TypeObject::UNDEFINED)
{
}
GameObject::GameObject(Animation animation_, sf::IntRect rect_, int hp_, int idx_line_, TypeObject type_)
	: animation(animation_),
	rect(rect_),
	hp(hp_),
	idx_line(idx_line_),
	type(type_)
{
}

// методы

// геттеры, сеттеры
TypeObject GameObject::getType() const
{
	return type;
}
Animation GameObject::getAnimetion() const
{
	return animation;
}
sf::IntRect GameObject::getRect() const
{
	return rect;
}
int GameObject::getHp() const
{
	return hp;
}
int GameObject::getIdxLine() const
{
	return idx_line;
}