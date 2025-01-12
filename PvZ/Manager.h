#pragma once
#include "Message.h"
#include "Map.h"
#include "LoadTexture.h"
#include "Peashooter.h"
#include <list>

class Manager
{
private:
	int win_wid;
	int win_hei;

	static Manager* born;
	std::list<GameObject*> game_objects;
	std::list<Message*> message;
	Map* map;

	struct {
		sf::Texture plant;
		sf::Texture zombie;
	} Texture;
	struct {
		sf::Font newRoman;
	} Font;

	Manager();
	Manager(Map* map_);
	//Manager(const Manager&);
	~Manager();
public:
	static Manager* GetBorn();
	void addMessage(Message msg);
	void setMap(Map* map_);
	void UpdateAll(double dt); // сообщения
	void update(double dt); // физика
	void LoadTextures(Identificate id, sf::Texture* texture, sf::IntRect rect, const std::string filename);
	void drawAll(sf::RenderWindow& win);

	void PrintObject();
};