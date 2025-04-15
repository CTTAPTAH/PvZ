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
	// ѕерва€ волна Ч сразу
	waves.emplace_back(0, std::vector<TypeEntity>{
		TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE
	});

	// ¬тора€ волна через 20 секунд
	waves.emplace_back(5, std::vector<TypeEntity>{
		TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::RAZOMBIE
	});

	// “реть€ через 40 секунд
	waves.emplace_back(5, std::vector<TypeEntity>{
		TypeEntity::CONUS_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::ZOMBIE
	});

	// ‘инальна€ волна через 60 секунд Ч жестче, но сбалансировано
	waves.emplace_back(5, std::vector<TypeEntity>{
		TypeEntity::DISCO_ZOMBIE,
			TypeEntity::ZOMBIE,
			TypeEntity::NEWSPAPER_ZOMBIE,
			TypeEntity::ZOMBIE
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
	// вычитаем единицу, т.к. последн€€ волна уже была выпущена
	if (cur_wave >= waves.size()) return;

	time_past += dt;
	// переходим к следующей волне, если нет зомби на карте или пришло врем€
	// ”словие "нет зомби" провер€етс€, если это не перва€ волна)
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
	GameObject* object = nullptr;

	int old_line = -1;
	int cur_line = -1;
	for (const auto& zm : waves[cur_wave].zombies) {
		if (zm == TypeEntity::ZOMBIE) {
			object = new Zombie(Rand(0, 4),
				Config::ZOMBIE_FRAME_WIDTH,
				Config::ZOMBIE_FRAME_HEIGHT);
		}
		else if (zm == TypeEntity::RAZOMBIE) {
			object = new RaZombie(Rand(0, 4),
				100,
				100);
		}
		else if (zm == TypeEntity::NEWSPAPER_ZOMBIE) {
			object = new NewspaperZombie(Rand(0, 4),
				100,
				100);
		}
		else if (zm == TypeEntity::CONUS_ZOMBIE) {
			object = new ConusZombie(Rand(0, 4));
		}
		else if (zm == TypeEntity::DISCO_ZOMBIE) {
			object = new DiscoZombie(Rand(0, 4));
		}
		else {
			return;
		}

		if (object) {
			// смещение от начальной при спавне, чтобы по€вл€лись не в одну линию
			sf::FloatRect rect_zm = object->getRect();
			cur_line = object->getIdxLine();
			if (cur_line == old_line) rect_zm.left += Rand(Config::SPAWN_OFFSET_MIN, Config::SPAWN_OFFSET_MAX);
			rect_zm.left += Rand(0, 10);
			object->setRect(rect_zm);
			
			// отправка сообщени€
			Message msg;
			msg.type = TypeMsg::CREATE;
			msg.create.new_object = object;
			Manager::getBorn()->addMessage(msg);

			old_line == object->getIdxLine();
		}
	}
}

// геттеры, сеттеры