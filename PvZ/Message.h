#pragma once
#include "GameObject.h"
#include "Map.h"

enum class TypeMsg { 
	UNDEFINED, DAMAGE, DEATH, CREATE, MOVE, ADD_MAP };
class Message
{
public:
	GameObject* object;
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
			Position old_pos;
		} move;
		struct {
			GameObject* plant;
			int x; 
			int y;
			int disp_x;
			int disp_y;
			int width;
			int height;
			sf::Color color;
			sf::Texture* texture;
		} add_map;

	};
	Message();
	Message(const Message&);
	~Message();
};