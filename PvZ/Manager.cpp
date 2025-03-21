#include "Manager.h"

Manager* Manager::born = nullptr;

<<<<<<< HEAD
Manager::Manager() : game_objects(), message(), loader(new LoadTexture) {
	win_wid = 800; win_hei = 600;
	born = nullptr;
	map = nullptr;
	textures = loader->GetTexturesList();
	//textures = loader->GetTexturesList();
	Texture.plant;
	Texture.zombie;

	Font.newRoman;
=======
// ������������, �����������
Manager::Manager() : game_objects(), messages() {
	win_wid = Config::WIN_WIDTH; win_hei = Config::WIN_HEIGHT;
	born = nullptr;
	for (int i = 0; i < Config::AMOUNT_LINES_MAP; i++) {
		zombie_on_line[i] = 0;
	}
>>>>>>> Добавлено:
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

<<<<<<< HEAD
Manager* Manager::GetBorn() {
	if (!born) born = new Manager;
	return born;
}
//bool Manager::addTexture(const std::string& name, const std::string& filename)
//{
//	sf::Texture texture;
//
//	if (!LoadTexture::loadFromFile(texture, filename)) {
//		return false; // ������ �������� ��������
//	}
//
//	textures[name] = std::move(texture); // ����������, � �� ��������.
//	// � sf::Texture ��� ������������ �����������
//
//	return true;
//}
sf::Texture* Manager::GetTexture(const std::string& name) {
	auto it = textures.find(name);
	return (it != textures.end()) ? &it->second : nullptr;
}

=======
// ������
>>>>>>> Добавлено:
void Manager::addMessage(Message msg) {
	messages.push_back(new Message(msg)); // ������ ����� ��������� � ����
}
void Manager::updateMessage(double dt) {
	for (auto& msg : messages) {
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
				obj->receiveMsg(msg);
			}
		}
	}
	messages.clear();
}
void Manager::updateObject(double dt, sf::RenderWindow& win) // ��� �������
{
	for (auto& obj : game_objects) {
		obj->update(dt, win);
	}
	// ���������� �������� � ����� C++:
	// ��������� ��, ��� � ������ ����� auto* � auto - ��� ���� � �� ��
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

// ��� ��������
void Manager::printObjects() const
{
	int count = 0;
	for (auto& obj : game_objects) {
		count++;
		printf_s("%d: �������: %d-%d\n", count, obj->getRect().left,
			obj->getRect().top);
	}
}
void Manager::printMessages() const
{
	int count = 0;
	for (auto& msg : messages) {
		count++;
		printf_s("%d: ��������� ����: ", count);
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
		printf_s("����� %d: %d\n", i, zombie_on_line[i]);
	}
}

// �������, �������
Manager* Manager::getBorn() {
	if (!born) born = new Manager;
	return born;
}
int Manager::getWinWidth()
{
	return win_wid;
}
<<<<<<< HEAD
//void Manager::LoadTextures()
//{
//	if (loader) {
//		textures = loader->GetTexturesList();
//	}
//}
std::list<GameObject*> Manager::getListObject() {
=======
int Manager::getWinHeight()
{
	return win_hei;
}
std::list<GameObject*> Manager::getListObject() const {
>>>>>>> Добавлено:
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
int Manager::getZombieOnLine(int idx_line) const
{
	return zombie_on_line[idx_line];
}