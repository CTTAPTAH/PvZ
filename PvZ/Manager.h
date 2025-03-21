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
<<<<<<< HEAD


	static Manager* born;
	std::list<GameObject*> game_objects;
	std::list<Message*> message;
	std::map<std::string, sf::Texture> textures;
	int zombie_on_line[5]; // 5 желательно заменить на переменную или define
	Map* map; // может и не надо

	LoadTexture* loader;

	struct {
		sf::Texture plant;
		sf::Texture zombie;
	} Texture;
	struct {
		sf::Font newRoman;
	} Font;
=======
	static Manager* born;
	std::list<GameObject*> game_objects;
	std::list<Message*> messages;
	int zombie_on_line[Config::AMOUNT_LINES_MAP];
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:

	Manager();
	~Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
public:
<<<<<<< HEAD
	static Manager* GetBorn();

	//bool addTexture(const std::string& name, const std::string& filename);

	void LoadTextures();
	sf::Texture* GetTexture(const std::string& name);

=======
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:
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