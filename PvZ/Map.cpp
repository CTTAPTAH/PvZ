#include "Map.h"
#include "Message.h"
#include "Peashooter.h"
#include "Melonpult.h"
#include "Chomper.h"
#include "Nut.h"
#include "SnowPeashooter.h"

// конструкторы, деструктор
Map::Map()
	: sprite(),
	amount_field_w(Config::AMOUNT_FIELD_W),
	amount_field_h(Config::AMOUNT_FIELD_H)
{
	setTexture(LoadTexture::getBorn().getTexture("map"));

	Manager* mng = Manager::getBorn();
	resizeGrid({ 0, 0, (float)mng->getWinWidth(),(float) mng->getWinHeight() });
}
Map::Map(sf::FloatRect rect_map)
	:sprite(),
	amount_field_w(Config::AMOUNT_FIELD_W),
	amount_field_h(Config::AMOUNT_FIELD_H)
{
	setTexture(LoadTexture::getBorn().getTexture("map"));
	resizeGrid(rect_map);
}

// методы 
void Map::resizeGrid(sf::FloatRect rect_map)
{
	rect = rect_map;
	field_width = rect.width / amount_field_w;
	field_height = rect.height / amount_field_h;

	//sprite.setTextureRect(rect);
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
bool Map::isValidIndex(int row, int col) const
{
	if (row < 0 or row >= amount_field_h or col < 0 or col >= amount_field_w) {
		return false;
	}
	return true;
}
bool Map::isValidIndex(sf::Vector2f vect) const
{
	return isValidIndex(vect.x, vect.y);
}
void Map::receiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::ADD_PLANT) {
		sf::Vector2f mousePos(int(msg->add_plant.mousePos.x), int(msg->add_plant.mousePos.y));
		sf::Vector2f idxPlant = getFieldIdx(mousePos);

		// Мышку тыкнули на карту или нет. Занята ли ячейка
		if ((idxPlant.y < 0 or idxPlant.y >= amount_field_w) or
			(idxPlant.x < 0 or idxPlant.x >= amount_field_h)
			or getIsPlaced(idxPlant.x, idxPlant.y)) {
			return;
		}
		if (msg->add_plant.type == TypeEntity::UNDEFINED) {
			return;
		}

		Manager* mng = Manager::getBorn();
		Message new_msg;
		new_msg.type = TypeMsg::CREATE;

		if (msg->add_plant.type == TypeEntity::PEASHOOTER) {
			Peashooter* pea = new Peashooter(getFieldPosition(idxPlant.x, idxPlant.y), idxPlant.x);
			new_msg.create.new_object = pea;
		}
		else if (msg->add_plant.type == TypeEntity::SUNFLOWER) {
			Sunflower* sunflower = new Sunflower(getFieldPosition(idxPlant.x, idxPlant.y), idxPlant.x);
			new_msg.create.new_object = sunflower;
		}
		else if (msg->add_plant.type == TypeEntity::WALLNUT) {
			Nut* nut = new Nut(idxPlant.x, getFieldPosition(idxPlant.x, idxPlant.y));
			new_msg.create.new_object = nut;
		}
		else if (msg->add_plant.type == TypeEntity::CHOMPER) {
			Chomper* chomper = new Chomper(idxPlant.x, getFieldPosition(idxPlant.x, idxPlant.y));
			new_msg.create.new_object = chomper;
		}
		else if (msg->add_plant.type == TypeEntity::SNOWPEASHOOTER) {
			SnowPeashooter* snowpea = new SnowPeashooter(idxPlant.x, getFieldPosition(idxPlant.x, idxPlant.y));
			new_msg.create.new_object = snowpea;
		}
		else if (msg->add_plant.type == TypeEntity::MELLONPULT) {
			Melonpult* melon = new Melonpult(getFieldPosition(idxPlant.x, idxPlant.y), idxPlant.x);
			new_msg.create.new_object = melon;
		}
		SoundEditor::getBorn()->playSound("plant", 30);
		mng->addMessage(new_msg);
		setIsPlaced(idxPlant.x, idxPlant.y, true);
	}
}

// для откладки
void Map::printIsPlaced()
{
	for (int i = 0; i < amount_field_h; i++) {
		for (int j = 0; j < amount_field_h; j++) {
			if (isPlaced[i][j])
				std::cout << "1 " << std::endl;
			else
				std::cout << "0 " << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------" << std::endl;
}

// геттеры, сеттеры
bool Map::getIsPlaced(int row, int col) const
{
	if (!isValidIndex(row, col)) {
		//std::cout << "Ошибка класса map, метода getIsPlaced: указан неверный индекс" << std::endl;
		return false;
	}
	return isPlaced[row][col];
}
int Map::getFieldWidth() const
{
	return field_width;
}
int Map::getFieldHeight() const
{
	return field_height;
}
sf::Vector2f Map::getFieldPosition(int i, int j) const
{
	if (!isValidIndex(i, j)) {
		std::cout << "Ошибка класса map, метода getFieldPosition: указан неверный индекс" << std::endl;
		return { 0, 0 };
	}
	return { rect.left + j * field_width, rect.top + i * field_height };
}
sf::Vector2f Map::getFieldPosition(sf::Vector2f vect) const
{
	return getFieldPosition(vect.x, vect.y);
}
sf::Vector2f Map::getFieldIdx(sf::Vector2f point) const {
	// Проверяем, находится ли точка внутри границ карты
	if (!rect.contains(point)) {
		return sf::Vector2f(-1, -1); // Точка вне карты
	}

	// Вычисляем индексы ячейки
	int col = (point.x - rect.left) / field_width;
	int row = (point.y - rect.top) / field_height;

	return sf::Vector2f(row, col);
}
sf::FloatRect Map::getRect() const
{
	return rect;
}
void Map::setRectMap(sf::FloatRect rect_map)
{
	resizeGrid(rect_map);
}
void Map::setTexture(sf::Texture* texture_)
{
	texture = texture_;
	if (texture) sprite.setTexture(*texture);
}
void Map::setIsPlaced(int row, int col, bool isPlaced_)
{
	if (!isValidIndex(row, col)) {
		std::cout << "Ошибка класса map, метода setIsPlaced: указан неверный индекс" << std::endl;
		return;
	}

	isPlaced[row][col] = isPlaced_;
}
void Map::setIsPlaced(sf::Vector2f vect, bool isPlaced_)
{
	setIsPlaced(vect.x, vect.y, isPlaced_);
}
