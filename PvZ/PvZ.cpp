#include <iostream>
#include "Manager.h"
#include "Peashooter.h"
#include "Map.h"
#include"Zombie.h"
#include "Sunflower.h"
#include"Car.h"
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
int win_width = Config::WIN_WIDTH, win_height = Config::WIN_HEIGHT;
//int w_cell = win_width / 9, h_cell = win_height / 5;// в конфиг
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
		music.setVolume(40);
		music.play();
	}

	SoundBuffer bufer;
	Sound zombies_are_comming;
	if (!bufer.loadFromFile("sounds\\zombies.ogg")) {
		cerr << "Ошибка воспроизведения звука" << endl;
		return 0;
	}
	zombies_are_comming.setBuffer(bufer);
	zombies_are_comming.setVolume(80);
	bool sound_played = false;

	Manager* mng = Manager::getBorn();
	LoadTexture& loader = LoadTexture::getBorn();
	loader.loadAllTexture();

	Map map({ 258, 81, 732, 493 });

	RenderWindow win(VideoMode(win_width, win_height), "PVZ");

	// создание машин
	for (int i = 0; i < 5; i++) {
		Car * car = new Car(i, TypeObject::UNDEFINED, map.getFieldWidth(), map.getFieldHeight());
		Message msg;
		msg.type = TypeMsg::CREATE;
		msg.create.new_object = car;
		mng->addMessage(msg);
	}

	// создание подсолнуха
	for (int i = 0; i < 5; i++) {
		Vector2i pos = map.getFieldPosition(i, 0);
		Sunflower* sun_flower = new Sunflower(
			i,
			TypeObject::PLANT,
			pos.x,
			pos.y
		);
		Message msg;
		msg.type = TypeMsg::CREATE;
		msg.create.new_object = sun_flower;
		mng->addMessage(msg);
	}

	// Создание гороха
	for (int i = 0; i < 5; i++) {
		Peashooter* pea = new Peashooter(map.getFieldPosition(i, 1), i);
		Message msg;
		msg.type = TypeMsg::CREATE;
		msg.create.new_object = pea;
		mng->addMessage(msg);
	}

	const double set_time = 3;
	double timer = set_time;

	const double music_set_time = 5;
	double music_timer = music_set_time;

	Event ev;
	while (win.isOpen()) {
		FPS();
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
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
			int w_cell = map.getFieldWidth();
			int h_cell = map.getFieldHeight();
			Zombie* zombie = new Zombie(Random(0, 4), TypeObject::ZOMBIE, w_cell, h_cell);
			Message zombie_msg;
			zombie_msg.type = TypeMsg::CREATE;
			zombie_msg.create.new_object = zombie;
			mng->addMessage(zombie_msg);
		}

		win.clear();
		map.drawMap(win); // сначала рисуем карту

		mng->updateMessage(fps.dt); // обрабатываем сообщения
		mng->updateObject(fps.dt, win); // объекты действуют и рисуются (можно разделить на действие и рисование)

		win.display();
	}

	win.close();

	return 0;
}