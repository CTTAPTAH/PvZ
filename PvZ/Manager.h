#pragma once
#include "Message.h"
#include "LoadTexture.h"
#include <list>

class Manager
{
private:
	int win_wid;
	int win_hei;

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

	Manager();
	Manager(const Manager&);
	~Manager();
public:
	static Manager* GetBorn();
	void UpdateAll(double dt);
	void LoadTextures(sf::Texture jump, UnitId id);
};