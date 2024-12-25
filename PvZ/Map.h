#pragma once
#include <SFML/Graphics.hpp>

struct Field {
	bool placed;
	sf::IntRect pos;
	sf::Texture texture;
};

class Map
{
private:
	int win_wid;
	int win_hei;
	Field fields[5][9];
public:
	Map();
	Map(int win_wid_, int win_hei_);

	void add(int x, int y, int disp_x, int disp_y, sf::Texture texture);
	void draw_all();
	void draw_map(sf::RenderWindow& win);
};