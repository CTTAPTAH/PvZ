#pragma once
#include "GameObject.h"
#include "Map.h"

enum class TypeMsg { DAMAGE, DEATH, CREATE, MOVE, ADD_MAP };
class Message
{
public:
	GameObject* object;
	TypeMsg type;

	union {
		struct {
			double damage;
		} damage;
		struct {
			GameObject* creature;
		} death;
		struct {
			GameObject* new_object;
		} create;
		struct {
			Position old_pos;
		} move;
		struct {
			int x; 
			int y;
			int disp_x;
			int disp_y;
			sf::Texture texture;
		} add_map;

	};
};

