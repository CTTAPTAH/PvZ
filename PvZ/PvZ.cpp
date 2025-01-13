#include <iostream>
#include "Manager.h"
#include "Peashooter.h"
#include "Map.h"
#include"Zombie.h"
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

struct Dt
{
	Clock clock;
	const double fps = 60.0;
	double newtime, lasttime = clock.getElapsedTime().asSeconds();
	double dt;

};
int win_width = 800, win_height = 600;// в конфиг
int w_cell = win_width / 9, h_cell = win_height / 5;// в конфиг
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

int main()
{
	system("chcp 1251>nul");

	Texture test_texture;
	Manager* mng = Manager::GetBorn();
	Map map(win_width, win_height, win_width / 9.0f, win_height / 5.0f);
	mng->setMap(&map);

	RenderWindow win(VideoMode(win_width, win_height), "PVZ");

	//Texture* texture;
	IntRect rect;
	//MGR->LoadTextures(Identificate::PEA, texture, rect, "file.png");

    //Sprite sprite(*texture);

	for (int i = 0; i < 5; i++) {
		Peashooter* pea = new Peashooter(0, TypeObject::PEASHOOTER);
		Message msg;
		msg.type = TypeMsg::ADD_MAP;
		msg.add_map.plant = pea;
		msg.add_map.disp_x = 10;
		msg.add_map.disp_y = 10;
		msg.add_map.texture = nullptr;
		msg.add_map.x = 0;
		msg.add_map.y = i;
		msg.add_map.width = 50;
		msg.add_map.height = 50;
		msg.add_map.color = { 0, 255, 0, 255 };
		mng->addMessage(msg);
	}
	//Cоздание зомби
	Zombie* zombie = new Zombie(2, TypeObject::ZOMBIE, w_cell, h_cell);
	Message zombie_msg;
	zombie_msg.type = TypeMsg::CREATE;
	zombie_msg.create.new_object = zombie;
	mng->addMessage(zombie_msg);

	Event ev;
	while (win.isOpen()) {
		FPS();
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
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