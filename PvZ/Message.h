#pragma once
#include "GameObject.h"

enum class TypeMsg { 
	UNDEFINED, DAMAGE, DEATH, CREATE, MOVE, ADD_PLANT, SET_MONEY
};
class Message
{
public:
	TypeMsg type;

	union {
		struct {
			double damage;
			GameObject* who_receive;
		} damage;
		struct {
			GameObject* creature;
		} death;
		struct {
			GameObject* new_object;
		} create;
		struct {
			sf::IntRect old_pos; // �������� ����� �� IntRect
		} move;
		struct {
			sf::Vector2f mousePos;
			TypeEntity type;
			int cost;
			int idx;
		} add_plant;
		struct {
			int money;
		} set_money;

	};
	Message();
	Message(const Message&);
	~Message();
};