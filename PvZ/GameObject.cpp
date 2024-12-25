#include "GameObject.h"

GameObject::GameObject()
{
	pos = { 0, 0 };
	hp = 0;
	idx_line = -1;
	id = -1;
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
	return Position();
}

void GameObject::SendMsg(double dt)
{
}

void GameObject::ReceiveMsg(Message* msg)
{
}
