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
	bool isPlaced[Config::AMOUNT_FIELD_H][Config::AMOUNT_FIELD_W] = { false };

	// при изменении размера карты, мен€ем и размер €чейки
	void resizeGrid(sf::IntRect rect_map);
public:
	// конструкторы, деструкторы
	Map();
	Map(sf::IntRect rect_map);
	~Map() = default;

	// методы
	void drawMap(sf::RenderWindow& win) const;
	void remove(int i, int j);
	void clear();
	bool isValidIndex(int row, int col) const;
	bool isValidIndex(sf::Vector2i vect) const;
	void receiveMsg(Message* msg);
	
	// дл€ откладки
	void printIsPlaced();

	// геттеры, сеттеры
	bool getIsPlaced(int row, int col) const;
	int getFieldWidth() const;
	int getFieldHeight() const;
	sf::Vector2i getFieldPosition(int i, int j) const;
	sf::Vector2i getFieldPosition(sf::Vector2i vect) const;
	sf::Vector2i getFieldIdx(sf::Vector2i point) const;
	sf::IntRect getRect() const;
	void setRectMap(sf::IntRect rect_map);
	void setTexture(sf::Texture* texture_);
	void setIsPlaced(int row, int col, bool isPlaced_);
	void setIsPlaced(sf::Vector2i vect, bool isPlaced_);
};