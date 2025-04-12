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
	// ������������, �����������
	Animation(sf::Texture* texture_, int frame_width_, int frame_height_, int count_frame_, double frametime, sf::Vector2f position);
	Animation(sf::Texture* texture_); // ����� �� ������������. ����� ������ ���� �������� ��������� ����
	Animation();
	Animation(const Animation& other);

	// ������
	void update(double dt);
	void draw(sf::RenderWindow& win);

	// �������, �������
	void setTexture(sf::Texture* texture_);
	void setPosition(float x, float y);
	void setScale(float x, float y);
	void setFrameSize(int frame_w, int frame_h);
};
