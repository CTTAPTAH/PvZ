#include <iostream>
#include "Manager.h"
#include "Map.h"
using namespace std;
using namespace sf;

int win_width = 800, win_height = 600;

int main()
{
	system("chcp 1251>nul");

	Texture test_texture;
	Manager* mng = Manager::GetBorn();
	Map map(win_width, win_height, win_width / 9.0f, win_height / 5.0f);
	mng->setMap(&map);

	RenderWindow win(VideoMode(win_width, win_height), "PVZ");

	Texture* texture;
	IntRect rect;
	MGR->LoadTextures(Identificate::PEA, texture, rect, "file.png");

    Sprite sprite(*texture);


	while (win.isOpen()) {
		Event ev;
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
		}
		win.clear();
		map.drawMap(win);
		win.display();
	}

	win.close();

	return 0;
}