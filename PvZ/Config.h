#pragma once

class Config
{
public:
	// Размеры экрана получает manager, при дальнейшё работе программы
	// лучше не пользоваться этими значениями, а получать их через manager,
	// т.к. размеры окна могут меняться
	static constexpr int WIN_WIDTH = 1399;
	static constexpr int WIN_HEIGHT = 600;

	static constexpr int W_CELL = 81;
	static constexpr int H_CELL = 98;
	// Игрок
	static constexpr int PLANT_COUNT = 5;

	// Интерфейс
	static constexpr int FRAME_ICON_OFFSET_X = -4;
	static constexpr int FRAME_ICON_OFFSET_Y = -1;
	static constexpr int ICON_OFFSET_X = 15;
	static constexpr int ICON_OFFSET_Y = 0;
	static constexpr int ICON_SPACING = 5;

	static constexpr int BOARD_POS_X = 150;
	static constexpr int BOARD_POS_Y = 0;

	static constexpr int SHOVEL_POS_X = 333;
	static constexpr int SHOVEL_POS_Y = 0;

	// Карта
	// Количество линий на карте
	static constexpr int AMOUNT_LINES_MAP = 5;

	// Количество ячеек в длину и высоту
	static constexpr int AMOUNT_FIELD_W = 9;
	static constexpr int AMOUNT_FIELD_H = 5;

	// Горох
	static constexpr double PEASHOOTER_DAMAGE = 1.0;
	static constexpr double PEASHOOTER_TIME_RELOAD = 1.0;
	static constexpr int PEASHOOTER_HP = 4;
	static constexpr int PEASHOOTER_FRAME_WIDTH = 100;
	static constexpr int PEASHOOTER_FRAME_HEIGHT = 100;
	static constexpr int PEASHOOTER_COUNT_FRAME = 1;//23
	static constexpr double PEASHOOTER_FRAMETIME = 0;//0.085
	static constexpr int PEASHOOTER_PROJECTILE_OFFSET_X = 72;
	static constexpr int PEASHOOTER_PROJECTILE_OFFSET_Y = 13;

	// Горошина снаряд
	static constexpr double PEA_PROJECTILE_SPEED = 300.0;
	static constexpr int PEA_PROJECTILE_HP = 1;
	static constexpr int PEA_PROJECTILE_FRAME_WIDTH = 20;
	static constexpr int PEA_PROJECTILE_FRAME_HEIGHT = 20;
	static constexpr int PEA_PROJECTILE_COUNT_FRAME = 1;
	static constexpr double PEA_PROJECTILE_FRAMETIME = 0;

	// Арбуз
	static constexpr double MELONPULT_DAMAGE = 1.0;
	static constexpr double MELONPULT_TIME_RELOAD = 1.0;
	static constexpr int MELONPULT_HP = 4;
	static constexpr int MELONPULT_FRAME_WIDTH = 100;
	static constexpr int MELONPULT_FRAME_HEIGHT = 84;
	static constexpr int MELONPULT_COUNT_FRAME = 1;
	static constexpr double MELONPULT_FRAMETIME = 0;
	static constexpr int MELONPULT_PROJECTILE_OFFSET_X = 72;
	static constexpr int MELONPULT_PROJECTILE_OFFSET_Y = 13;

	// Снаряд арбуза
	static constexpr double MELON_VY = -300.0;
	static constexpr int MELON_HP = 1;
	static constexpr int MELON_FRAME_WIDTH = 52;
	static constexpr int MELON_FRAME_HEIGHT = 44;
	static constexpr int MELON_COUNT_FRAME = 1;
	static constexpr double MELON_FRAMETIME = 0;
	static constexpr double MELON_GRAVITY = 300;

	//Зомби
	static constexpr int ZOMBIE_FRAME_WIDTH = 100;
	static constexpr int ZOMBIE_FRAME_HEIGHT = 100;
	static constexpr int ZOMBIE_FRAME_COUNT = 1;
	static constexpr int ZOMBIE_FRAME_TIME = 0;

	static constexpr int DEFAULT_ZOMBIE_HP = 4;
	static constexpr double DEFAULT_ZOMBIE_SPEED = 100;
	static constexpr double FROZEN_DEFAULT_ZOMBIE_SPEED = 20;

	static constexpr int DEFAULT_ZOMBIE_TIME_RELOAD = 1;
	static constexpr int DEFAULT_ZOMBIE_RELOAD = 0;
	static constexpr int DEFAULT_ZOMBIE_DAMAGE = 1;
	static constexpr int DEFAULT_ZOMBIE_IDLE_SPEED = 0;






	//Подсолнух
	static constexpr int SUNFLOWER_FRAME_WIDTH = 100;
	static constexpr int SUNFLOWER_FRAME_HEIGHT = 100;
	static constexpr int SUNFLOWER_FRAME_COUNT = 20;
	static constexpr double SUNFLOWER_FRAME_TIME = 0.085;

	static constexpr int SUNFLOWER_HP = 4;
	static constexpr int TIME_TO_REAPEAR_SUN = 7;

	//Солнца

	static constexpr int SUN_FRAME_WIDTH = 50;
	static constexpr int SUN_FRAME_HEIGHT = 50;
	static constexpr int SUN_FRAME_COUNT = 1;
	static constexpr int SUN_FRAME_TIME = 0;

	//Орех
	static constexpr int NUT_FRAME_WIDTH = 100;
	static constexpr int NUT_FRAME_HEIGHT = 100;
	static constexpr int NUT_FRAME_COUNT = 1;
	static constexpr int NUT_FRAME_TIME = 0;

	static constexpr int NUT_HP = 12;

	//Машинки
	static constexpr int CAR_FRAME_WIDTH = 100;
	static constexpr int CAR_FRAME_HEIGHT = 60;
	static constexpr int CAR_FRAME_COUNT = 1;
	static constexpr int CAR_FRAME_TIME = 0;

	//Чомпер
	static constexpr int CHOMPER_FRAME_WIDTH = 100;
	static constexpr int CHOMPER_FRAME_HEIGHT = 100;
	static constexpr int CHOMPER_FRAME_COUNT = 10;
	static constexpr double CHOMPER_FRAME_TIME = 0.07;
	static constexpr int CHOMPER_HP = 4;

};