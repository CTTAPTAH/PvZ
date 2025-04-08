#pragma once
#include <string.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "manager.h"

enum class TypeEntity;

struct PlantInfo {
	sf::Texture* icon = nullptr;
	int cost = 0;
	TypeEntity type;

	PlantInfo(sf::Texture* icon_, int cost_, TypeEntity type_);
};

class Player
{
private:
	std::vector<PlantInfo> plant_slots;
public:
	// конструктор, деструктор
	Player();
	Player(const std::vector<PlantInfo>& plant_slots_);

	// методы

	// геттеры, сеттеры
	void setPlantSlots(const std::vector<PlantInfo>& plant_slots_);
};