#pragma once
#include "Manager.h"


struct PlantInfo;

class UIManager
{
private:
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
	void createPlantSelection(const std::vector<PlantInfo>& plants);
	void draw(sf::RenderWindow& win);
	void handleMousePress(sf::Vector2f mousePos);
	void handleMouseRelease(sf::Vector2f mousePos);

	// �������, �������
};

