#include <iostream>
#include "Map.h"
using namespace std;
using namespace sf;

int main()
{
	Map map(800, 600);
	system("chcp 1251>nul");

	system("chcp 1251>0");
	RenderWindow win(VideoMode(800, 600), "PVZ");

	while (win.isOpen()) {
		Event ev;
		while (win.pollEvent(ev)) {
			if (ev.type == Event::Closed)
				win.close();
		}
		win.clear();
		map.draw_map(win);
		win.display();
	}

	win.close();

	return 0;
}