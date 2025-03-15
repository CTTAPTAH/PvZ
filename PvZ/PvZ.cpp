#include <iostream>
#include "Manager.h"
#include "Peashooter.h"
#include "Map.h"
#include"Zombie.h"
#include "Sunflower.h"
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
	fps.dt = fps.newtime - fps.lasttime; // ¬рем€ всех операций между кадрами
	if (fps.dt < fps.fps) {
		sleep(sf::seconds(1 / fps.fps - fps.dt)); // «адержка, чтобы fps был равен указанном у
		fps.newtime = fps.clock.getElapsedTime().asSeconds();
		fps.dt = fps.newtime - fps.lasttime; // ¬рем€ всех операций между кадрами + задержка
	}
	fps.lasttime = fps.newtime;
	
}
int Random(int start, int end) {
	return rand() % (end - start + 1) + start;
}
//void LoadAllTextures()
//{
//	Manager* mng = Manager::GetBorn();
//	mng->addTexture("peashooter", "texture\\peashooter.png");
//}

int main()
{
	srand(time(0));
	system("chcp 1251>nul");

	Texture test_texture;
	Manager* mng = Manager::GetBorn();
	//mng->LoadTextures();
	//LoadAllTextures();
	Map map(win_width, win_height, win_width / 9.0f, win_height / 5.0f);
	mng->setMap(&map);

	RenderWindow win(VideoMode(win_width, win_height), "PVZ");

	//Texture* texture;
	IntRect rect;
	//MGR->LoadTextures(Identificate::PEA, texture, rect, "file.png");
    //Sprite sprite(*texture);
	// —оздание гороха
	// 
	for (int i= 0; i < 5; i++) {
		Sunflower* sunflower = new Sunflower(i, TypeObject::PLANT,20, i*map.getFieldHeight());
		IntRect rect = { 0 * map.getFieldWidth(), i * map.getFieldHeight(), 50,50 };
		sunflower->setRect(rect);
		Message msg;
		msg.type = TypeMsg::CREATE;
		msg.create.new_object = sunflower;
		mng->addMessage(msg);
	}




	//for (int i = 0; i < 5; i++) {
	//	Peashooter* pea = new Peashooter(i, TypeObject::PEASHOOTER);
	//	IntRect rect = { 0 * map.getFieldWidth(),
	//		i * map.getFieldHeight(),
	//		50, 50 }; // 10 - это смещение относительно €чейки карты
	//	pea->setRect(rect);
	//	Message msg;
	//	msg.type = TypeMsg::CREATE;
	//	msg.create.new_object = pea;
	//	mng->addMessage(msg);
	/*	msg.type = TypeMsg::ADD_MAP;
		msg.add_map.plant = pea;
		msg.add_map.disp_x = 10;
		msg.add_map.disp_y = 10;
		msg.add_map.texture = nullptr;
		msg.add_map.x = 0;
		msg.add_map.y = i;
		msg.add_map.width = 50;
		msg.add_map.height = 50;
		msg.add_map.color = { 0, 255, 0, 255 };
		mng->addMessage(msg);*/
	//}
	//Cоздание зомбb
	
	//Peashooter* pea = new Peashooter(2, TypeObject::PEASHOOTER);
	//IntRect rec= { 0 * map.getFieldWidth(),
	//	2 * map.getFieldHeight(),
	//	50, 50 }; // 10 - это смещение относительно €чейки карты
	//pea->setRect(rec);
	//Message msg;
	//msg.type = TypeMsg::CREATE;
	//msg.create.new_object = pea;
	//mng->addMessage(msg);
	//

	const double set_time = 4;
	double timer = set_time;

	Event ev;
	while (win.isOpen()) {
		FPS();
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
		}
		// —павнер зомби
		timer -= fps.dt;
		if (timer <= 0) {
			timer = set_time;
			Zombie* zombie = new Zombie(Random(0,4), TypeObject::ZOMBIE, w_cell, h_cell);
			Message zombie_msg;
			zombie_msg.type = TypeMsg::CREATE;
			zombie_msg.create.new_object = zombie;
			mng->addMessage(zombie_msg);
		}

		win.clear();
		map.drawMap(win); // сначала рисуем карту

		mng->updateMessage(fps.dt); // обрабатываем сообщени€
		mng->updateObject(fps.dt, win); // объекты действуют и рисуютс€ (можно разделить на действие и рисование)

		win.display();
		//mng->PrintObject();
	}

	win.close();

	return 0;
}