#include "Map.h"

Map::Map()
{
	win_wid = 800;
	win_hei = 600;
}
Map::Map(int win_wid_, int win_hei_)
{
	win_wid = win_wid_;
	win_hei = win_hei_;
}

void Map::add(int x, int y, int disp_x, int disp_y, sf::Texture texture) {
	sf::IntRect pos;
	pos.left = (x * win_wid / 9.0f) + disp_x;
	pos.top = (y * win_hei / 5.0f) + disp_y;
	fields[x][y] = { true, pos, texture };
}
void Map::draw_all() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			sf::IntRect rect = fields[i][j].pos;
			//SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
			//SDL_RenderFillRect(ren, &rect);
		}
	}
}

void Map::draw_map(sf::RenderWindow& win)
{
	sf::FloatRect rect = {0, 0, win_wid / 9.0f,win_hei / 5.0f };
	sf::RectangleShape rectangle;
	for (int i = 0; i < 5; i++) {
		rect.left = 0;
		for (int j = 0; j < 9; j++) {
			rectangle.setPosition(rect.left, rect.top);
			rectangle.setSize(sf::Vector2f(rect.width, rect.height));
			rectangle.setFillColor(sf::Color::Red);
			win.draw(rectangle);

			rectangle.setOutlineColor(sf::Color::White);
			rectangle.setOutlineThickness(2.0f);
			win.draw(rectangle);

			rect.left += win_wid / 9.0f;
		}
		rect.top += win_hei / 5.0f;
	}
}
