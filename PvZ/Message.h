#pragma once
#include "GameObject.h"

enum class TypeMsg { 
	UNDEFINED, DAMAGE, DEATH, CREATE, MOVE, ADD_PLANT };
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
			sf::IntRect old_pos; // возможно будет не IntRect
		} move;
		struct {
			sf::Vector2f mousePos;
			TypeEntity type;
			int cost;
		} add_plant;

	};
	Message();
	Message(const Message&);
	~Message();
};