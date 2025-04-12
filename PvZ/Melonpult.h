#pragma once
#include "Manager.h"
#include "Message.h"

class Melonpult : public Peashooter
{
protected:
	bool is_shooting;
	double damage;
	double time_reload;
	double reload;
public:
	// ������������, �����������
	Melonpult();
	Melonpult(sf::Vector2f pos, int idx_line_);
	~Melonpult() = default;

	// ������
	void isShooting(double dt) override;

	// �������, �������
};
