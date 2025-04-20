#pragma once
#include "config.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

struct PlantInfo;
class Manager;

class UIManager
{
private:
	// ����� ���� �����
	sf::Vector2f bar_size;
	sf::Vector2f bar_pos;
	sf::RectangleShape wave_bar_border;     // �����
	sf::RectangleShape wave_bar_background; // ���
	sf::RectangleShape wave_bar_fill;       // ����������� �����
	bool waves_started;
	sf::Sprite head_zm;

	// ���������� ������
	sf::Font font;
	sf::Text money_text;
	int money;

	// ������ �� ���������, ���������� ��������� ��������
	bool isPreviewing;
	sf::Color color_indicator;

	// ������� �� ������
	bool chosen_shovel;

	// ����� ��������
	std::vector<PlantInfo> plant_infos;
	int chosenPlantIdx;
	sf::Sprite frame_icon;

	// ������� ��� ������
	std::vector<sf::Sprite> plant_icons;
	sf::Sprite board;
	sf::Sprite shovel;
public:
	// �����������, ����������
	UIManager();

	// ������
	void updateInfo();
	void updateWaves(double progress_ratio);
	void createPlantSelection(const std::vector<PlantInfo>& plants);
	void draw(sf::RenderWindow& win);
	void handleMousePress(sf::Vector2f mousePos);
	void handleMouseRelease(sf::Vector2f mousePos);
	void receiveMsg(Message* msg);
	void updateMoneyText(int money_);

	// �������, �������
};

