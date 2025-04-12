#include "GameObject.h"

// конструкторы, деструкторы
GameObject::GameObject()
	: animation(),
	rect{ 0, 0, 0, 0 },
	hp(0),
	idx_line(0),
	type_obj(TypeObject::UNDEFINED),
	type_ent(TypeEntity::UNDEFINED)

{
}
GameObject::GameObject(Animation animation_, sf::FloatRect rect_, int hp_, int idx_line_, TypeObject type_obj_, TypeEntity type_ent_)
	: animation(animation_),
	rect(rect_),
	hp(hp_),
	idx_line(idx_line_),
	type_obj(type_obj_),
	type_ent(type_ent_)
{
}

// методы

// геттеры, сеттеры
Animation GameObject::getAnimetion() const
{
	return animation;
}
sf::FloatRect GameObject::getRect() const
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
bool GameObject::getIsDead() const
{
	return isdead;
}
TypeObject GameObject::getTypeObj() const
{
	return type_obj;
}
TypeEntity GameObject::getTypeEnt() const
{
	return type_ent;
}
void GameObject::setRect(sf::FloatRect rect_)
{
	rect = rect_;
	animation.setPosition(rect.left, rect.top);
}

void GameObject::setDead(bool isHappend)
{
	isdead = isHappend;
}
