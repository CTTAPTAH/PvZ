#include "Player.h"
#include "manager.h" // должен быть в .cpp

PlantInfo::PlantInfo(sf::Texture* icon_, int cost_, TypeEntity type_,
	double time_reload_)
	: icon(icon_), cost(cost_), type(type_),
	reload(0), time_reload(Config::COOLDOWN_DEFAULT)
{
}

// конструктор, деструктор
Player::Player()
	: plant_slots(),
	money(Config::MONEY)
{
	//setMoney(Config::MONEY);
}
Player::Player(const std::vector<PlantInfo>& plant_slots_)
	: plant_slots(plant_slots_),
	money(Config::MONEY)
{
	//setMoney(Config::MONEY);
}

// методы
void Player::updateInfo(double dt)
{
	for (int i = 0; i < plant_slots.size(); i++) {
		if (plant_slots[i].reload > 0) {
			plant_slots[i].reload -= dt;
		}
	}
}
void Player::resetCooldown(int idx)
{
	plant_slots[idx].reload = plant_slots[idx].time_reload;
}

// геттеры, сеттеры
void Player::setPlantSlots(const std::vector<PlantInfo>& plant_slots_)
{
	plant_slots = std::move(plant_slots_);
}
void Player::setMoney(int money_)
{
	money = money_;

	Message msg;
	msg.type = TypeMsg::SET_MONEY;
	msg.set_money.money = money;

	Manager::getBorn()->addMessage(msg);
}

int Player::getMoney() const
{
	return money;
}

std::vector<PlantInfo> Player::getPlantSlots() const
{
	return plant_slots;
}
