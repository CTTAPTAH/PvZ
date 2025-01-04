#include "Map.h"
#include "Message.h"

// конструктор
Map::Map()
{
	win_width = 800;
	win_height = 600;
	map_x = map_y = 0;

	field_width = win_width / 9.0f;
	field_height = win_height / 5.0f;
}
Map::Map(int win_width_, int win_height_, int field_width_, int field_height_)
{
	win_width = win_width_;
	win_height = win_height_;
	map_x = map_y = 0;

	field_width = field_width_;
	field_height = field_height_;
}

// геттеры, сеттеры
Field Map::getField(int x, int y) {
	return fields[x][y];
}
bool Map::isFieldTree(int x, int y) {
	return fields[x][y].isPlaced;
}
sf::Vector2i Map::getFieldIndex(int x, int y) {
	int i = x / field_width;
	int j = y / field_height;

	return { i, j };
}
void Map::setTexture(sf::Texture new_texture, int x, int y)
{
	fields[x][y].texture = new_texture;
}
void Map::setMapX(int x) {
	map_x = x;
}
void Map::setMapY(int y) {
	map_y = y;
}

// методы
void Map::receiveMsg(Message* message) {
	if (message->type == TypeMsg::ADD_MAP) {
		int x = message->add_map.x;
		int y = message->add_map.y;
		int disp_x = message->add_map.disp_x;
		int disp_y = message->add_map.disp_y;
		sf::Texture* texture = message->add_map.texture;

		if (fields[x][y].isPlaced) {
			return;
		}

		add(x, y, disp_x, disp_y, texture);
	}
}
void Map::add(int x, int y, int disp_x, int disp_y, sf::Texture* texture) {
	sf::IntRect pos;
	pos.left = x * field_width + disp_x;
	pos.top = y * field_height + disp_y;
	// убрать или добавить в дальнейшем (будут текстуры)
	pos.width = 25;
	pos.height = 25;
	// убрать или добавить в дальнейшем (будут текстуры)

	fields[x][y] = { true, pos, *texture };
}
void Map::drawMap(sf::RenderWindow& win)
{
	sf::IntRect rect = { map_x, map_y, field_width, field_height };
	sf::RectangleShape rectangle;
	for (int i = 0; i < 5; i++) {
		rect.left = map_x;
		for (int j = 0; j < 9; j++) {
			// Отрисовка красных квадратов (в будущем карта)
			rectangle.setPosition(rect.left, rect.top);
			rectangle.setSize(sf::Vector2f(rect.width, rect.height));
			rectangle.setFillColor(sf::Color::Red);
			win.draw(rectangle);

			// Отрисовка контуров (в будущем карта)
			rectangle.setOutlineColor(sf::Color::White);
			rectangle.setOutlineThickness(2.0f);
			win.draw(rectangle);

			rect.left += field_width;
		}
		rect.top += field_height;
	}
	drawAllPlants(win);
}
void Map::drawAllPlants(sf::RenderWindow& win) {
	for (int i = 0; i < amount_field_w; i++) {
		for (int j = 0; j < amount_field_h; j++) {
			if (fields[i][j].isPlaced) {
				sf::RectangleShape rectangle;
				sf::IntRect rect = fields[i][j].pos;
				rectangle.setPosition(rect.left, rect.top);
				rectangle.setSize(sf::Vector2f(rect.width, rect.height));
				rectangle.setFillColor(sf::Color::Green);
				win.draw(rectangle);
			}
		}
	}
}
void Map::remove(int x, int y) {
	fields[x][y] = Field();
}
void Map::clear() {
	for (int i = 0; i < amount_field_w; i++) {
		for (int j = 0; j < amount_field_h; j++) {
			fields[i][j] = Field();
		}
	}
}
