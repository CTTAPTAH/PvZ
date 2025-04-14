#pragma once
#include <vector>
#include "GameObject.h"

class manager;

struct Wave {
	double start_time;
	std::vector<TypeEntity> zombies;

	Wave(double start_time_, std::vector<TypeEntity> zombies_);
};

class WaveManager
{
private:
	double time_past;
	int cur_wave;
	std::vector<Wave> waves;
	void initWaves();
public:
	// конструкторы, деструкторы
	WaveManager();
	WaveManager(const WaveManager& other);
	~WaveManager() = default;

	// методы
	void update(double dt);
	bool hasZombies();
	void spawn();

	// геттеры, сеттеры
};