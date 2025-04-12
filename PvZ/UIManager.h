#pragma once
#include "Manager.h"


struct PlantInfo;

class UIManager
{
private:
	// Рисуем ли индиактор, помогающий поставить растение
	bool isPreviewing;
	sf::Color color_indicator;

	// выбрана ли лопата
	bool chosen_shovel;

	// выбор растения
	std::vector<PlantInfo> plant_infos;
	int chosenPlantIdx;
	sf::Sprite frame_icon;

	// спрайты для иконок
	std::vector<sf::Sprite> plant_icons;
	sf::Sprite board;
	sf::Sprite shovel;
public:
	// конструктор, деструктор
	UIManager();

	// методы
	void createPlantSelection(const std::vector<PlantInfo>& plants);
	void draw(sf::RenderWindow& win);
	void handleMousePress(sf::Vector2f mousePos);
	void handleMouseRelease(sf::Vector2f mousePos);

	// геттеры, сеттеры
};

