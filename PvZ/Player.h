#pragma once
#include <string.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "manager.h"

enum class TypeObject;

struct PlantInfo {
	sf::Texture* icon = nullptr;
	int cost = 0;
	TypeObject type;

	PlantInfo(sf::Texture* icon_, int cost_, TypeObject type_);
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