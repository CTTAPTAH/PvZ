#include "WaveManager.h"
// чтобы избежать циклических зависимостей, то нижнее подлкючаем в .cpp
#include "Manager.h"
#include "RaZombie.h"
#include "NewspaperZombie.h"
#include "ConusZombie.h"
#include "DiscoZombie.h"

int Rand(int start, int end) {
	return rand() % (end - start + 1) + start;
}

Wave::Wave(double start_time_, std::vector<TypeEntity> zombies_)
	: start_time(start_time_),
	zombies(zombies_)
{
}

void WaveManager::initWaves()
{
	// 1 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::ZOMBIE
	});

	// 2 волна
	waves.emplace_back(30, std::vector<TypeEntity>{
		TypeEntity::ZOMBIE
	});

	// 3 волна
	waves.emplace_back(28, std::vector<TypeEntity>{
			TypeEntity::ZOMBIE
	});

	// 4 волна
	waves.emplace_back(25, std::vector<TypeEntity>{
		TypeEntity::CONUS_ZOMBIE
	});

	// 5 волна
	waves.emplace_back(23, std::vector<TypeEntity>{
		TypeEntity::RAZOMBIE,
			TypeEntity::RAZOMBIE
	});

	// 6 волна
	waves.emplace_back(25, std::vector<TypeEntity>{
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE
	});

	// 7 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE
	});

	// 8 волна
	waves.emplace_back(25, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE
	});

	// 9 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE
	});

	// 10 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::RAZOMBIE
	});

	// 11 волна
	waves.emplace_back(25, std::vector<TypeEntity>{
		TypeEntity::CONUS_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE
	});

	// 12 волна
	waves.emplace_back(27, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::DISCO_ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE
	});

	// 13 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::RAZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE
	});

	// 14 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE
	});

	// 15 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::RAZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::ZOMBIE
	});

	// 16 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::ZOMBIE
	});

	// 17 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::ZOMBIE
	});

	// 18 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::CONUS_ZOMBIE
	});

	// 19 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::CONUS_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::ZOMBIE
	});

	// 20 волна
	waves.emplace_back(20, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::DISCO_ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::RAZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::CONUS_ZOMBIE,
			TypeEntity::CONUS_ZOMBIE
	});
}

// конструкторы, деструкторы
WaveManager::WaveManager()
	: time_past(0),
	cur_wave(0)
{
	initWaves();
}
WaveManager::WaveManager(const WaveManager& other)
{
	time_past = other.time_past;
	cur_wave = other.cur_wave;
	waves = other.waves;
}

// методы
void WaveManager::update(double dt)
{
	// вычитаем единицу, т.к. последняя волна уже была выпущена
	if (cur_wave >= waves.size()) return;

	time_past += dt;
	// переходим к следующей волне, если нет зомби на карте или пришло время
	// Условие "нет зомби" проверяется, если это не первая волна)
	if ((!hasZombies() and cur_wave != 0) or
		time_past >= waves[cur_wave].start_time) {
		spawn();
		cur_wave++;
		time_past = 0;

		// спавним зомби у следующей волны волны
	}
}

bool WaveManager::hasZombies()
{
	auto objects = Manager::getBorn()->getListObject();
	for (const auto& obj : objects) {
		// чомпер может ломать
		if (obj->getTypeObj() == TypeObject::ZOMBIE) {
			Zombie* zm = dynamic_cast<Zombie*>(obj);
			if (zm) {
				if (zm->getIsDead()) continue;
			}
			return true;
		}
	}

	return false;
}
void WaveManager::spawn()
{
	Manager* mng = Manager::getBorn();
	// чтобы равномерно ставились зомби:
	int size = 5;
	int free_lines[5] = { 0, 1, 2, 3, 4 };
	int idx;

	// если зомби больше, чем линий, то смещаем их относительно прощлых зомби
	int offset_on_line[5] = { 0, 0, 0, 0, 0 };

	GameObject* object = nullptr;
	
	int line;
	for (const auto& zm : waves[cur_wave].zombies) {
		// выбираем линию
		if (size > 0) {
			idx = Rand(0, size - 1);
			line = free_lines[idx];
			std::swap(free_lines[idx], free_lines[size - 1]);
			--size;
		}
		else {
			size = 5;
		}

		// создаём выбранного зомби
		if (zm == TypeEntity::ZOMBIE) {
			object = new Zombie(line,
				Config::ZOMBIE_FRAME_WIDTH,
				Config::ZOMBIE_FRAME_HEIGHT);
		}
		else if (zm == TypeEntity::RAZOMBIE) {
			object = new RaZombie(line,
				100,
				100);
		}
		else if (zm == TypeEntity::NEWSPAPER_ZOMBIE) {
			object = new NewspaperZombie(line,
				100,
				100);
		}
		else if (zm == TypeEntity::CONUS_ZOMBIE) {
			object = new ConusZombie(line);
		}
		else if (zm == TypeEntity::DISCO_ZOMBIE) {
			object = new DiscoZombie(line);
		}
		else {
			return;
		}

		if (object) {
			// смещение от начальной позиции при спавне,
			// чтобы появлялись не в одну линию
			sf::FloatRect rect_zm = object->getRect();
			rect_zm.left += Rand(Config::SPAWN_OFFSET_MIN,
				Config::SPAWN_OFFSET_MAX) + offset_on_line[line];
			object->setRect(rect_zm);

			// запоминаем позицию спавна, чтобы не было "зомби в зомби"
			offset_on_line[line] = (rect_zm.left + rect_zm.width) / 2; // с учётом ширины
			
			// отправка сообщения
			Message msg;
			msg.type = TypeMsg::CREATE;
			msg.create.new_object = object;
			mng->addMessage(msg);

		}
	}
	mng->getUI().updateWaves(double(cur_wave + 1) / double(waves.size()));
	std::cout << "Заспавнили волну: " << cur_wave + 1 << std::endl;
}

// геттеры, сеттеры