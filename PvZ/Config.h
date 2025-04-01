#pragma once

class Config
{
public:
	// Размеры экрана получает manager, при дальнейшё работе программы
	// лучше не пользоваться этими значениями, а получать их через manager,
	// т.к. размеры окна могут меняться
	static constexpr int WIN_WIDTH = 1399;
	static constexpr int WIN_HEIGHT = 600;

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
	static constexpr int PEASHOOTER_HP = 1;
	static constexpr int PEASHOOTER_FRAME_WIDTH = 100;
	static constexpr int PEASHOOTER_FRAME_HEIGHT = 100;
	static constexpr int PEASHOOTER_COUNT_FRAME = 23;
	static constexpr double PEASHOOTER_FRAMETIME = 0.085;
	static constexpr int PEASHOOTER_PROJECTILE_OFFSET_X = 72;
	static constexpr int PEASHOOTER_PROJECTILE_OFFSET_Y = 13;

	// Горошина
	static constexpr double PEA_PROJECTILE_SPEED = 300.0;
	static constexpr int PEA_PROJECTILE_HP = 1;
	static constexpr int PEA_PROJECTILE_FRAME_WIDTH = 20;
	static constexpr int PEA_PROJECTILE_FRAME_HEIGHT = 20;
	static constexpr int PEA_PROJECTILE_COUNT_FRAME = 1;
	static constexpr double PEA_PROJECTILE_FRAMETIME = 0;
};