#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
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
		win.display();
	}

	win.close();

	return 0;
}