#pragma once
#include "Config.h"
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
	std::list<Message*> messages;
	int zombie_on_line[Config::AMOUNT_LINES_MAP];

	Manager();
	~Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
public:
	void addMessage(Message msg);
	void updateMessage(double dt);
	void updateObject(double dt, sf::RenderWindow& win);

	void addZombieOnLine(int idx_line);
	void removeZombieOnLine(int idx_line);

	//для откладки
	void printObjects() const;
	void printMessages() const;
	void printWinSize() const;
	void printZombieOnLine() const;

	// геттеры, сеттеры
	static Manager* getBorn();
	int getWinWidth();
	int getWinHeight();
	std::list<GameObject*> getListObject() const;
	std::vector<sf::IntRect> getZombieRects() const;
	int getZombieOnLine(int idx_line) const;
};