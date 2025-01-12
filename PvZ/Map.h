#pragma once
#include <SFML/Graphics.hpp>

class Message;

struct Field {
	bool isPlaced = false;
	// Замена текстуры
	sf::IntRect pos{ 0, 0, 0, 0 };
	sf::Color color{ 0, 0, 0, 0 };
	//sf::Texture texture;
};

class Map
{
private:
	const int amount_field_w = 9, amount_field_h = 5;
	int map_x, map_y; // в какой точке на экране начинается карта
	int field_width, field_height;
	int win_width, win_height;
	Field fields[9][5];
public:
	Map();
	Map(int win_width_, int win_height_, int field_width_, int field_height_);

	Field getField(int x, int y);
	bool isFieldTree(int x, int y);
	sf::Vector2i getFieldIndex(int x, int y);
	void setTexture(sf::Texture new_texture, int x, int y);
	void setMapX(int x);
	void setMapY(int y);

	bool addPlant(Message* message);
	void drawMap(sf::RenderWindow& win);
	void drawAllPlants(sf::RenderWindow& win);
	void remove(int x, int y);
	void clear();
};