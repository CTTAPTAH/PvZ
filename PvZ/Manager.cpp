#include "Manager.h"

Manager* Manager::born = nullptr;

// конструкторы, деструкторы
Manager::Manager()
	: game_objects(),
	messages(),
	map({ 258, 81, 732, 493 }),
	ui(),
	player()
{
	win_wid = Config::WIN_WIDTH; win_hei = Config::WIN_HEIGHT;
	born = nullptr;
	for (int i = 0; i < Config::AMOUNT_LINES_MAP; i++) {
		zombie_on_line[i] = 0;
	}

}
Manager::~Manager() {
	for (auto& obj : game_objects) {
		delete obj;
	}
	game_objects.clear();

	for (auto& msg : messages) {
		delete msg;
	}
	messages.clear();

	delete born;
	born = nullptr;
}

// методы
void Manager::addMessage(Message msg) {
	messages.push_back(new Message(msg)); // Создаём копию сообщения в куче

}
void Manager::updateMessage(double dt) {
	for (auto& msg : messages) {
		// Сообщение для manager
		if (msg->type == TypeMsg::DEATH) {
			auto res = std::find(game_objects.begin(), game_objects.end(), msg->death.creature);
			if (res != game_objects.end()) {
				delete* res; // удаляем сам объект
				game_objects.erase(res);
			}// удаляем указатель на объект в списке
		}
		else if (msg->type == TypeMsg::CREATE) {
			game_objects.push_back(msg->create.new_object);
		}

		// Сообщение для game_object
		if (msg->type == TypeMsg::DAMAGE or
			msg->type == TypeMsg::MOVE) {
			for (auto obj : game_objects) {
				obj->receiveMsg(msg);
			}
		}

		// сообщение для map
		if (msg->type == TypeMsg::ADD_PLANT) {
			map.receiveMsg(msg);
		}

		// сообщение для UIManager
		if (msg->type == TypeMsg::SET_MONEY) {
			ui.receiveMsg(msg);
		}
	}
	messages.clear();
}
void Manager::updateObject(double dt, sf::RenderWindow& win) // Для позиции
{
	for (auto& obj : game_objects) {
		obj->update(dt, win);
	}
	// интересная тонкость в языке C++:
	// интересно то, что в ДАННОМ цикле auto* и auto - это одно и то же
}

void Manager::addZombieOnLine(int idx_line)
{
	if (0 <= idx_line and idx_line <= Config::AMOUNT_LINES_MAP) {
		zombie_on_line[idx_line]++;
	}
}
void Manager::removeZombieOnLine(int idx_line)
{
	if (0 <= idx_line and idx_line <= Config::AMOUNT_LINES_MAP) {
		if (zombie_on_line[idx_line] > 0)
			zombie_on_line[idx_line]--;
	}
}

// для откладки
void Manager::printObjects() const
{
	int count = 0;
	for (auto& obj : game_objects) {
		count++;
		printf_s("%d: Позиция: %d-%d\n", count, obj->getRect().left,
			obj->getRect().top);
	}
}
void Manager::printMessages() const
{
	int count = 0;
	for (auto& msg : messages) {
		count++;
		printf_s("%d: Сообщение типа: ", count);
		switch (msg->type) {
		case TypeMsg::DAMAGE:
			printf_s("damage"); break;
		case TypeMsg::CREATE:
			printf_s("create"); break;
		case TypeMsg::DEATH:
			printf_s("death"); break;
		case TypeMsg::MOVE:
			printf_s("move"); break;
		default:
			printf_s("undefind"); break;
		}
		printf_s("\n");
	}
}
void Manager::printWinSize() const
{
	printf_s("win width: %d\nwin_height: %d\n", win_wid, win_hei);
}
void Manager::printZombieOnLine() const
{
	for (int i = 0; i < Config::AMOUNT_LINES_MAP; i++) {
		printf_s("Линия %d: %d\n", i, zombie_on_line[i]);
	}
}

// геттеры, сеттеры
Manager* Manager::getBorn() {
	if (!born) born = new Manager;
	return born;
}
Map& Manager::getMap()
{
	return map;
}
int Manager::getWinWidth() const
{
	return win_wid;
}
int Manager::getWinHeight() const
{
	return win_hei;
}
std::list<GameObject*> Manager::getListObject() const {
	return game_objects;
}
//Функция для создания списка ректов исключительно зомби
std::vector<sf::IntRect> Manager::getZombieRects() const {
	std::vector<sf::IntRect> zombieRects;
	for (auto obj : game_objects) {
		if (obj->getTypeObj() == TypeObject::ZOMBIE) {
			zombieRects.push_back(obj->getRect());
		}
	}
	return zombieRects;
}
int Manager::getZombieOnLine(int idx_line) const
{
	return zombie_on_line[idx_line];
}
UIManager& Manager::getUI()
{
	return ui;
}

Player& Manager::getPlayer()
{
	return player;
}
