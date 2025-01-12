#include "GameObject.h"

GameObject::GameObject()
{
	// временно место текстуры
	rect.left = 0; rect.top = 0; rect.width = 50; rect.height = 50;
	color.r = 0; color.g = 0; color.b = 0; color.a = 0;
	// То, что было
	pos = { 0, 0 };
	hp = 0;
	texture = nullptr;
	idx_line = -1;
	type = TypeObject::UNDEFINED;
}
GameObject::GameObject(Position pos_, int hp_, int idx_line_, TypeObject type_)
{
	// временно вместо текстуры
	rect.left = 0; rect.top = 0; rect.width = 50; rect.height = 50;
	color.r = 0; color.g = 0; color.b = 0; color.a = 0;
	// То, что было
	pos = pos_;
	hp = hp_;
	idx_line = idx_line_;
	type = type_;
}
GameObject::GameObject(const GameObject&)
{
}
GameObject::~GameObject()
{
}

void GameObject::ReceiveDamage()
{

}
void GameObject::Update()
{
}
void GameObject::UpdatePosition(double dt, double speed)
{

}
void GameObject::Animation(double dt)
{
}
void GameObject::Collision()
{
}
Position GameObject::GetPosition()
{
	return pos;
}
void GameObject::draw(sf::RenderWindow& win)
{
}
void GameObject::setPosition(Position pos_)
{
	pos = pos_;
}
void GameObject::SendMsg(double dt)
{
}
void GameObject::ReceiveMsg(Message* msg)
{

}
