#pragma once
#include "config.h"
#include <SFML/Graphics.hpp>

class Message;

class Map
{
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	int amount_field_w, amount_field_h;
	sf::IntRect rect;
	int field_width, field_height;
	bool isPlaced[Config::AMOUNT_FIELD_W][Config::AMOUNT_FIELD_H] = { false };

	// при изменении размера карты, мен€ем и размер €чейки
	void resizeGrid(sf::IntRect rect_map);
	bool isValidIndex(int i, int j) const;
public:
	// конструкторы, деструкторы
	Map();
	Map(sf::IntRect rect_map);
	~Map() = default;

	// методы
	void drawMap(sf::RenderWindow& win) const;
	void remove(int i, int j);
	void clear();

	// геттеры, сеттеры
	bool getIsPlaced(int i, int j) const;
	int getFieldWidth() const;
	int getFieldHeight() const;
	sf::Vector2i getFieldPosition(int i, int j) const;
	void setRectMap(sf::IntRect rect_map);
	void setTexture(sf::Texture* texture_);
};