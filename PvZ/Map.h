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
	sf::FloatRect rect;
	int field_width, field_height;
	bool isPlaced[Config::AMOUNT_FIELD_H][Config::AMOUNT_FIELD_W] = { false };

	// при изменении размера карты, мен€ем и размер €чейки
	void resizeGrid(sf::FloatRect rect_map);

public:
	// конструкторы, деструкторы
	Map();
	Map(sf::FloatRect rect_map);
	~Map() = default;

	// методы
	void drawMap(sf::RenderWindow& win) const;
	void remove(int i, int j);
	void clear();
	bool isValidIndex(int row, int col) const;
	bool isValidIndex(sf::Vector2f vect) const;
	void receiveMsg(Message* msg);
	
	// дл€ откладки
	void printIsPlaced();

	// геттеры, сеттеры
	bool getIsPlaced(int row, int col) const;
	int getFieldWidth() const;
	int getFieldHeight() const;
	sf::Vector2f getFieldPosition(int i, int j) const;
	sf::Vector2f getFieldPosition(sf::Vector2f vect) const;
	sf::Vector2f getFieldIdx(sf::Vector2f point) const;
	sf::FloatRect getRect() const;
	void setRectMap(sf::FloatRect rect_map);
	void setTexture(sf::Texture* texture_);
	void setIsPlaced(int row, int col, bool isPlaced_);
	void setIsPlaced(sf::Vector2f vect, bool isPlaced_);
};