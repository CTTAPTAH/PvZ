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

	Manager();
	Manager(Map* map_);
	//Manager(const Manager&);
	~Manager();
public:
	static Manager* GetBorn();

	//bool addTexture(const std::string& name, const std::string& filename);

	void LoadTextures();
	sf::Texture* GetTexture(const std::string& name);

	void addMessage(Message msg);
	void setMap(Map* map_);
	Map* getMap();
	void updateMessage(double dt); // сообщения
	void updateObject(double dt, sf::RenderWindow& win); // физика объектов и рисуем объекты
	//void LoadTextures(Identificate id, sf::Texture* texture, sf::IntRect rect, const std::string filename);
	std::list<GameObject*> getListObject();
	std::vector<sf::IntRect> getZombieRects() const;
	void PrintObject();

	void addZombieOnLine(int idx_line);
	void removeZombieOnLine(int idx_line);
	int getZombieOnLine(int idx_line);
};