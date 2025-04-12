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
	// конструкторы, деструкторы
	Animation(sf::Texture* texture_, int frame_width_, int frame_height_, int count_frame_, double frametime, sf::Vector2f position);
	Animation(sf::Texture* texture_); // лучше не использовать. Можно только ради быстроты написания кода
	Animation();
	Animation(const Animation& other);

	// методы
	void update(double dt);
	void draw(sf::RenderWindow& win);

	// геттеры, сеттеры
	void setTexture(sf::Texture* texture_);
	void setPosition(float x, float y);
	void setScale(float x, float y);
	void setFrameSize(int frame_w, int frame_h);
};
