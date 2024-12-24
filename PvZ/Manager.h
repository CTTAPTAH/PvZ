#pragma once
#include "Message.h"
#include "LoadTexture.h"
#include <list>
#include <SFML/Graphics.hpp>

class Manager
{
private:
	static Manager* born;
	std::list<GameObject*> game_object;
	std::list<Message*> message;

	struct {
		sf::Texture plant;
		sf::Texture zombie;
	} Texture;
	struct {
		sf::Font newRoman;
	} Font;

	//Field fields[5][9];

	Manager() : game_object(), message() {};
	Manager(const Manager&) = delete;
public:
	~Manager() {
		game_object.clear();
		message.clear();
		delete born;
		born = nullptr;
	}
	Manager* GetBorn() {
		if (!born) born = new Manager;
		return born;
	}

	void UpdateAll(double dt) {
		for (auto obj : game_object) {
			obj->SendMsg(dt);
		}

		for (auto msg : message) {
			// Сообщение для manager
			if (msg->type == TypeMsg::DEATH) {
				auto res = std::find(game_object.begin(), game_object.end(), msg->death.creature);
				delete* res; // удаляем сам объект
				game_object.erase(res); // удаляем указатель на объект в списке
			}
			else if (msg->type == TypeMsg::CREATE) {
				game_object.push_back(msg->create.new_object);
			}

			// Сообщение для game_object
			if (msg->type == TypeMsg::DAMAGE or
				msg->type == TypeMsg::MOVE) {
				for (auto obj : game_object) {
					//obj->ReceiveMsg(*msg);
				}
			}
		}
	}
	//void LoadTextures(Text* jump, int id) {
	//}
};

Manager* Manager::born = nullptr;