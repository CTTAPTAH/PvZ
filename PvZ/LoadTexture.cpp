#include "LoadTexture.h"

// конструкторы, деструктор

// методы
void LoadTexture::addTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "Ошибка загрузки текстур: не удалось загрузить текстуру" << std::endl;
		return;
	}

	textures[name] = std::move(texture); // перемещаем, т.к. нет
	// конструктора копирования
}
void LoadTexture::loadAllTexture()
{
	// растения
	addTexture("peashooter", "textures\\peashooter.png");
	addTexture("sunflower", "textures\\Sunflower.png");
	addTexture("nut_full_hp", "textures\\Wallnut\\nut_full_hp.png");
	addTexture("nut_50_hp", "textures\\Wallnut\\nut_50_hp.png");
	addTexture("nut_low_hp", "textures\\Wallnut\\nut_low_hp.png");
	addTexture("melonpult", "textures\\melonpult.png");
	addTexture("snowpea", "textures\\snowpea.png");
	addTexture("chomper", "textures\\chomper.png");
	addTexture("chew", "textures\\chew.png");
	addTexture("snowpeaPr", "textures\\snowpeaPr.png");
	addTexture("nut_full_hp", "textures\\Wallnut\\nut_full_hp.png");
	addTexture("nut_50_hp", "textures\\Wallnut\\nut_50_hp.png");
	addTexture("nut_low_hp", "textures\\Wallnut\\nut_low_hp.png");
	addTexture("melonpult", "textures\\melonpult.png");

	// зомби
	addTexture("zombie", "textures\\zomsheet.png");
	addTexture("newszombie", "textures\\Zombies\\NewspaperZomb.png");
	addTexture("wnewszombie", "textures\\Zombies\\WithoutNewspaper.png");
	addTexture("razombie", "textures\\Zombies\\Ra_zombie.png");
	addTexture("razombie_tr", "textures\\Zombies\\RaZombieCAP.png");
	addTexture("conus_zombie1", "textures\\Zombies\\conus_zombie1.png");
	addTexture("conus_zombie2", "textures\\Zombies\\conus_zombie2.png");
	addTexture("conus_zombie3", "textures\\Zombies\\conus_zombie3.png");
	addTexture("disco_zombie", "textures\\Zombies\\disco_zombie.png");

	// иконки
	addTexture("peashooter_icon", "textures\\peasooter_icon.png");
	addTexture("sunflower_icon", "textures\\sunflower_icon.png");
	addTexture("wallnut_icon", "textures\\wallnut_icon.png");
	addTexture("snow_pea_icon", "textures\\snow_pea_icon.png");
	addTexture("cabbage_icon", "textures\\cabbage_icon.png");
	addTexture("chomper_icon", "textures\\chomper_icon.png");

	// другое
	addTexture("pea_projectile", "textures\\pea_projectile.png");
	addTexture("melon_projectile", "textures\\melon.png");
	addTexture("map", "textures\\map.png");
	addTexture("car", "textures\\Machine.png");
	addTexture("sun", "textures\\sun.png");
	addTexture("board", "textures\\board.png");
	addTexture("shovel", "textures\\shovel.png");
	addTexture("shovel2", "textures\\shovel2.png");
	addTexture("frame_icon", "textures\\frame_icon.png");
	addTexture("end_screen", "textures\\EndScreen.png");
}

// геттеры, сеттеры
LoadTexture& LoadTexture::getBorn()
{
	static LoadTexture born;
	return born;
}
sf::Texture* LoadTexture::getTexture(const std::string& name)
{
	auto it = textures.find(name);
	return (it != textures.end()) ? &it->second : nullptr;
}