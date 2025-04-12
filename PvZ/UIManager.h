#pragma once
#include "config.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

struct PlantInfo;
class Manager;

class UIManager
{
private:
	// Отображаем деньги
	sf::Font font;
	sf::Text money_text;
	int money;

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
	void updateInfo();
	void createPlantSelection(const std::vector<PlantInfo>& plants);
	void draw(sf::RenderWindow& win);
	void handleMousePress(sf::Vector2f mousePos);
	void handleMouseRelease(sf::Vector2f mousePos);
	void receiveMsg(Message* msg);
	void updateMoneyText(int money_);

	// геттеры, сеттеры
};

