#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	int frame_width, frame_height; // размер кадра
	int cur_frame; // текущий кадр для отображения
	int count_frame; // сколько всего кадров
	double frametime; // время обновления кадров
	double timer; // сколько времени прошло
public:
	Animation(sf::Texture* texture_, int frame_width_, int frame_height_, int count_frame_, double frametime);
	Animation(sf::Texture* texture_);
	Animation();

	void update(double dt);
	void draw(sf::RenderWindow& win);
	void setTexture(sf::Texture* texture_);
	void setPosition(int x, int y);
	void setScale(double x, double y);
};
