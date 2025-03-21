#pragma once
#include "GameObject.h"

enum class TypeMsg { 
	UNDEFINED, DAMAGE, DEATH, CREATE, MOVE };
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

	};
	Message();
	Message(const Message&);
	~Message();
};