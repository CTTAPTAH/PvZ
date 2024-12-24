#pragma once
#include <SFML/Graphics.hpp>

int win_wid = 800;
int win_hei = 600;

struct Field {
	bool placed;
	sf::IntRect pos;
	sf::Texture texture;
};

class Map
{
private:
	Field fields[5][9];
public:
	void add(int x, int y, int disp_x, int disp_y, sf::Texture texture) {
		sf::IntRect pos;
		pos.left = (x * win_wid / 9.0f) + disp_x;
		pos.top = (y * win_hei / 5.0f) + disp_y;
		fields[x][y] = { true, pos, texture };
	}
	void draw_all() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				//sf::IntRect rect = mas[i][j].rect_plant;
				//SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
				//SDL_RenderFillRect(ren, &rect);
			}
		}
	}
};