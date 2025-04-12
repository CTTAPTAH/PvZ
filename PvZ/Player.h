#pragma once
#include <string.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Message.h"
//#include "manager.h"

class Manager;
enum class TypeEntity;

struct PlantInfo {
	sf::Texture* icon = nullptr;
	int cost = 0;
	TypeEntity type;
	double reload;
	double time_reload;

	PlantInfo(sf::Texture* icon_, int cost_, TypeEntity type_,
		double time__reload_);
};

class Player
{
private:
	std::vector<PlantInfo> plant_slots;
	int money;
public:
	// конструктор, деструктор
	Player();
	Player(const std::vector<PlantInfo>& plant_slots_);

	// методы
	void updateInfo(double dt);
	void resetCooldown(int idx);

	// геттеры, сеттеры
	void setPlantSlots(const std::vector<PlantInfo>& plant_slots_);
	void setMoney(int money_);
	int getMoney() const;
	std::vector<PlantInfo> getPlantSlots() const;
};