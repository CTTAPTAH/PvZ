#include <iostream>
#include "Manager.h"
#include "Peashooter.h"
#include "Map.h"
#include"Zombie.h"
#include "Sunflower.h"
#include"Car.h"
#include "Nut.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


struct Dt
{
	Clock clock;
	const double fps = 60.0;
	double newtime = 0;
	double lasttime = clock.getElapsedTime().asSeconds();
	double dt = 0;

};
Dt fps;

void FPS()
{
	fps.newtime = fps.clock.getElapsedTime().asSeconds();
	fps.dt = fps.newtime - fps.lasttime; // Время всех операций между кадрами
	if (fps.dt < fps.fps) {
		sleep(sf::seconds(1 / fps.fps - fps.dt)); // Задержка, чтобы fps был равен указанном у
		fps.newtime = fps.clock.getElapsedTime().asSeconds();
		fps.dt = fps.newtime - fps.lasttime; // Время всех операций между кадрами + задержка
	}
	fps.lasttime = fps.newtime;

}
int Random(int start, int end) {
	return rand() % (end - start + 1) + start;
}

int main()
{
	srand(time(0));
	system("chcp 1251>nul");

	Music music;
	if (!music.openFromFile("sounds\\MUSIC.ogg")) {
		cerr << "Ошибка загрузки музыки!" << endl;
	}
	else {
		music.setLoop(true);
		music.setVolume(100);
		music.play();
	}

	SoundBuffer bufer;
	Sound zombies_are_comming;
	if (!bufer.loadFromFile("sounds\\zombies.ogg")) {
		cerr << "Ошибка воспроизведения звука" << endl;
		return 0;
	}
	zombies_are_comming.setBuffer(bufer);
	zombies_are_comming.setVolume(100);
	bool sound_played = false;

	LoadTexture& loader = LoadTexture::getBorn();
	loader.loadAllTexture();
	Manager* mng = Manager::getBorn();

	//Map map({ 258, 81, 732, 493 });

	RenderWindow win(VideoMode(mng->getWinWidth(), mng->getWinHeight()), "PVZ");

	//// создание машин
	for (int i = 0; i < 5; i++) {
		Manager* mng = Manager::getBorn();
		Car * car = new Car(i, TypeObject::UNDEFINED, mng->getMap().getFieldWidth(), mng->getMap().getFieldHeight());
		Message msg;
		msg.type = TypeMsg::CREATE;
		msg.create.new_object = car;
		mng->addMessage(msg);
	}

	// создание подсолнуха
	//for (int i = 0; i < 5; i++) {
	//	Vector2i pos = mng->getMap().getFieldPosition(i, 0);
	//	Sunflower* sun_flower = new Sunflower(
	//		i,
	//		TypeObject::PLANT,
	//		pos.x,
	//		pos.y
	//	);
	//	Message msg;
	//	msg.type = TypeMsg::CREATE;
	//	msg.create.new_object = sun_flower;
	//	mng->addMessage(msg);
	//}

	// Создание гороха
	//for (int i = 0; i < 5; i++) {
	//	Peashooter* pea = new Peashooter(mng->getMap().getFieldPosition(i, 1), i);
	//	Message msg;
	//	msg.type = TypeMsg::CREATE;
	//	msg.create.new_object = pea;
	//	mng->addMessage(msg);
	//}

	// создание интерфейса
	vector<PlantInfo> plant_slots;
	PlantInfo pea_info(LoadTexture::getBorn().getTexture("peashooter_icon"), 100, TypeEntity::PEASHOOTER);
	PlantInfo sunflower_info(LoadTexture::getBorn().getTexture("sunflower_icon"), 50, TypeEntity::SUNFLOWER);
	PlantInfo wallnut_info(LoadTexture::getBorn().getTexture("wallnut_icon"), 50, TypeEntity::WALLNUT);
	PlantInfo snow_pea_info(LoadTexture::getBorn().getTexture("snow_pea_icon"), 175, TypeEntity::UNDEFINED);
	PlantInfo cabbage_info(LoadTexture::getBorn().getTexture("cabbage_icon"), 100, TypeEntity::MELLONPULT);
	plant_slots.push_back(pea_info);
	plant_slots.push_back(sunflower_info);
	plant_slots.push_back(wallnut_info);
	plant_slots.push_back(snow_pea_info);
	plant_slots.push_back(cabbage_info);

	Player player(plant_slots);
	UIManager ui;
	ui.createPlantSelection(plant_slots);

	const double set_time = 8;
	double timer = set_time;

	const double music_set_time = 5;
	double music_timer = music_set_time;

	Event ev;
	while (win.isOpen()) {
		FPS();
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
			if (ev.type == sf::Event::MouseButtonPressed) {
				if (ev.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f mousePos = win.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
					ui.handleMousePress(mousePos);
				}
			}
			if (ev.type == sf::Event::MouseButtonReleased) {
				if (ev.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f mousePos = win.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
					ui.handleMouseRelease(mousePos);
				}
			}
		}


		music_timer -= fps.dt;
		if (!sound_played && music_timer <= music_set_time-3.5) {
			zombies_are_comming.play();
			sound_played = true;
		}

		// Спавнер зомби
		timer -= fps.dt;
		if (timer <= 0) {
			timer = Random(0, (int)set_time);
			Zombie* zombie = new Zombie(Random(0, 4));
			Message zombie_msg;
			zombie_msg.type = TypeMsg::CREATE;
			zombie_msg.create.new_object = zombie;
			mng->addMessage(zombie_msg);
		}

		win.clear();
		mng->getMap().drawMap(win); // сначала рисуем карту

		mng->updateMessage(fps.dt); // обрабатываем сообщения
		mng->updateObject(fps.dt, win); // объекты действуют и рисуются (можно разделить на действие и рисование)
		ui.draw(win);

		win.display();
	}

	win.close();

	return 0;
}