#include "Map.h"
#include "Message.h"
#include "Peashooter.h"

// конструкторы, деструктор
Map::Map()
	: sprite(),
	amount_field_w(Config::AMOUNT_FIELD_W),
	amount_field_h(Config::AMOUNT_FIELD_H)
{
	setTexture(LoadTexture::getBorn().getTexture("map"));

	Manager* mng = Manager::getBorn();
	resizeGrid({ 0, 0, mng->getWinWidth(), mng->getWinHeight() });
}
Map::Map(sf::IntRect rect_map)
	: sprite(),
	amount_field_w(Config::AMOUNT_FIELD_W),
	amount_field_h(Config::AMOUNT_FIELD_H)
{
	setTexture(LoadTexture::getBorn().getTexture("map"));
	resizeGrid(rect_map);
}

// методы 
void Map::resizeGrid(sf::IntRect rect_map)
{
	rect = rect_map;
	field_width = rect.width / amount_field_w;
	field_height = rect.height / amount_field_h;

	//sprite.setTextureRect(rect);
}
bool Map::isValidIndex(int i, int j) const
{
	if (i < 0 or i >= amount_field_h or j < 0 or j >= amount_field_w) {
		return false;
	}
	return true;
}

void Map::drawMap(sf::RenderWindow& win) const
{
	if (texture) {
		win.draw(sprite);
	}
}
void Map::remove(int i, int j)
{
	if (!isValidIndex(i, j)) {
		std::cout << "Ошибка класса map, метода remove: указан неверный индекс" << std::endl;
		return;
	}
	isPlaced[i][j] = false;
}
void Map::clear()
{
	memset(isPlaced, false, sizeof(isPlaced));
}

// геттеры, сеттеры
bool Map::getIsPlaced(int i, int j) const
{
<<<<<<< HEAD
	sf::IntRect rect = { map_x, map_y, field_width, field_height };
	sf::RectangleShape rectangle;
	for (int i = 0; i < 5; i++) {
		rect.left = map_x;
		for (int j = 0; j < 9; j++) {
			// Отрисовка красных квадратов (в будущем карта)
			rectangle.setPosition(rect.left, rect.top);
			rectangle.setSize(sf::Vector2f(rect.width, rect.height));
			rectangle.setFillColor(sf::Color::White);
			win.draw(rectangle);

			// Отрисовка контуров (в будущем карта)
			rectangle.setOutlineColor(sf::Color::Black);
			rectangle.setOutlineThickness(2.0f);
			win.draw(rectangle);

			rect.left += field_width;
		}
		rect.top += field_height;
=======
	if (!isValidIndex(i, j)) {
		std::cout << "Ошибка класса map, метода getIsPlaced: указан неверный индекс" << std::endl;
		return false;
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:
	}
	return isPlaced[i][j];
}
int Map::getFieldWidth() const
{
	return field_width;
}
int Map::getFieldHeight() const
{
	return field_height;
}
sf::Vector2i Map::getFieldPosition(int i, int j) const
{
	if (!isValidIndex(i, j)) {
		std::cout << "Ошибка класса map, метода getFieldPosition: указан неверный индекс" << std::endl;
		return { -1, -1 };
	}
	return { rect.left + j * field_width, rect.top + i * field_height };
}
void Map::setRectMap(sf::IntRect rect_map)
{
	resizeGrid(rect_map);
}
void Map::setTexture(sf::Texture* texture_)
{
	texture = texture_;
	if (texture) sprite.setTexture(*texture);
}