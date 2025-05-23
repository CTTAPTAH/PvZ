#pragma once
#include "Player.h"
#include "UIManager.h"
#include "Config.h"
#include "Message.h"
#include "Map.h"
#include "LoadTexture.h"
#include "Peashooter.h"
//#include "Melonpult.h"
#include "Sunflower.h"
#include "WaveManager.h"
#include <list>

class Manager
{
private:
	int win_wid;
	int win_hei;
	static Manager* born;
	Map map;
	Player player;
	UIManager ui;
	WaveManager wave_manager;
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

	//��� ��������
	void printObjects() const;
	void printMessages() const;
	void printWinSize() const;
	void printZombieOnLine() const;

	// �������, �������
	static Manager* getBorn();
	Map& getMap();
	int getWinWidth() const;
	int getWinHeight() const;
	std::list<GameObject*> getListObject() const;
	std::vector<sf::FloatRect> getZombieRects() const;
	int getZombieOnLine(int idx_line) const;
	UIManager& getUI();
	Player& getPlayer();
	WaveManager& getWaveManager();
};