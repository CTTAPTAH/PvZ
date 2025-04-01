#include "Player.h"

PlantInfo::PlantInfo(sf::Texture* icon_, int cost_, TypeObject type_)
	: icon(icon_), cost(cost_), type(type_)
{
}

// �����������, ����������
Player::Player()
	: plant_slots()
{

}
Player::Player(const std::vector<PlantInfo>& plant_slots_)
	: plant_slots(plant_slots_)
{
}

// ������

// �������, �������
void Player::setPlantSlots(const std::vector<PlantInfo>& plant_slots_)
{
	plant_slots = std::move(plant_slots_);
}
