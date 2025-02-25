#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Sprite sprite;
	sf::Texture* texture;
	int frame_width, frame_height; // ������ �����
	int cur_frame; // ������� ���� ��� �����������
	int count_frame; // ������� ����� ������
	double frametime; // ����� ���������� ������
	double timer; // ������� ������� ������
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
