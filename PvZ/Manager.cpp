#include "Manager.h"

Manager* Manager::born = nullptr;

Manager::Manager() : game_objects(), message() {
	win_wid = 800; win_hei = 600;
	born = nullptr;
	map = nullptr;

	Texture.plant;
	Texture.zombie;

	Font.newRoman;
}
//Manager::Manager(const Manager&) {}
Manager::~Manager() {
	for (auto obj : game_objects) {
		delete obj;
	}
	game_objects.clear();

	for (auto msg : message) {
		delete msg;
	}
	message.clear();

	delete born;
	born = nullptr;
}

Manager* Manager::GetBorn() {
	if (!born) born = new Manager;
	return born;
}
void Manager::addMessage(Message msg) {
	message.push_back(new Message(msg)); // ������ ����� ��������� � ����
}
void Manager::setMap(Map* map_) {
	map = map_;
}
Map* Manager::getMap()
{
	return map;
}
void Manager::updateMessage(double dt) {
	for (auto obj : game_objects) {
		obj->SendMsg(dt);
	}

	for (auto msg : message) {
		// ��������� ��� manager
		if (msg->type == TypeMsg::DEATH) {
			auto res = std::find(game_objects.begin(), game_objects.end(), msg->death.creature);
			delete* res; // ������� ��� ������
			game_objects.erase(res); // ������� ��������� �� ������ � ������
		}
		else if (msg->type == TypeMsg::CREATE) {
			game_objects.push_back(msg->create.new_object);
		}

		// ��������� ��� game_object
		if (msg->type == TypeMsg::DAMAGE or
			msg->type == TypeMsg::MOVE) {
			for (auto obj : game_objects) {
				obj->ReceiveMsg(msg);
			}
		}
		// ��������� ��� map
		else if (msg->type == TypeMsg::ADD_MAP) {
			if (map->addPlant(msg)) {
				game_objects.push_back(msg->add_map.plant);
			}
		}
	}

	//std::cout << game_objects.size() << std::endl;

	message.clear();
} // ��� ���������
void Manager::updateObject(double dt, sf::RenderWindow& win) // ��� �������
{
	for (auto obj : game_objects) {
		//// ���������, ����� �� ������ ��������
		//Peashooter* pea = dynamic_cast<Peashooter*>(obj);
		//if (pea) {
		//	pea->isShooting(dt);  // ���� ������ - Peashooter, �������� ��� ����� shoot()
		//}
		//Projectile* projectile = dynamic_cast<Projectile*>(obj);
		//if (projectile) {
		//	projectile->move(dt);
		//}
		obj->update(dt, win);
	}
}
void Manager::LoadTextures(Identificate id, sf::Texture* texture, sf::IntRect rect, const std::string filename) {
	//texture = loader->LoadingRecieveMSG1(texture, rect, filename);
	switch (id) {
	case Identificate::PEA:
		//Texture.plant = texture;
		break;
	case Identificate::ZOMBIE:
		//Texture.zombie = texture;
		break;
	}
	//��� ����� ��� ��������� ��������� �� ������ ��������
}

void Manager::PrintObject()
{
	int count = 0;
	for (auto obj : game_objects) {
		count++;
		printf_s("%d: %d-%d\n", count, obj->getRect().left,
			obj->getRect().top);
	}
}
void Manager::addZombieOnLine(int idx_line)
{
	if (0 <= idx_line and idx_line <= 4) {
		zombie_on_line[idx_line]++;
		//printf_s("���������� ����� �� %d �����: %d\n", idx_line, zombie_on_line[idx_line]);
	}
}
void Manager::removeZombieOnLine(int idx_line)
{
	if (0 <= idx_line and idx_line <= 4) {
		if (zombie_on_line[idx_line] > 0)
			zombie_on_line[idx_line]--;
		//printf_s("���������� ����� �� %d �����: %d\n", idx_line, zombie_on_line[idx_line]);
	}
}
int Manager::getZombieOnLine(int idx_line)
{
	return zombie_on_line[idx_line];
}
std::list<GameObject*> Manager::getListObject() {
	return game_objects;
}

//������� ��� �������� ������ ������ ������������� �����
std::vector<sf::IntRect> Manager::getZombieRects() const {
    std::vector<sf::IntRect> zombieRects;
    for (auto obj : game_objects) {
        if (obj->getType() == TypeObject::ZOMBIE) {
            zombieRects.push_back(obj->getRect());
        }
    }
    return zombieRects;
}