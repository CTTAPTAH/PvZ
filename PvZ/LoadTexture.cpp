#include "LoadTexture.h"

// ������������, ����������

// ������
void LoadTexture::addTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "������ �������� �������: �� ������� ��������� ��������" << std::endl;
		return;
	}

	textures[name] = std::move(texture); // ����������, �.�. ���
	// ������������ �����������
}
void LoadTexture::loadAllTexture()
{
	// ��������
	addTexture("peashooter", "textures\\peashooter.png");
	addTexture("sunflower", "textures\\Sunflower.png");
	addTexture("zombie", "textures\\zomsheet.png");

	addTexture("nut_full_hp", "textures\\Wallnut\\nut_full_hp.png");
	addTexture("nut_50_hp", "textures\\Wallnut\\nut_50_hp.png");
	addTexture("nut_low_hp", "textures\\Wallnut\\nut_low_hp.png");
	addTexture("melonpult", "textures\\melonpult.png");

	// ������
	addTexture("peashooter_icon", "textures\\peasooter_icon.png");
	addTexture("sunflower_icon", "textures\\sunflower_icon.png");
	addTexture("wallnut_icon", "textures\\wallnut_icon.png");
	addTexture("snow_pea_icon", "textures\\snow_pea_icon.png");
	addTexture("cabbage_icon", "textures\\cabbage_icon.png");

	// ������
	addTexture("pea_projectile", "textures\\pea_projectile.png");
	addTexture("melon_projectile", "textures\\melon.png");
	addTexture("map", "textures\\map.png");
	addTexture("car", "textures\\Machine.png");
	addTexture("sun", "textures\\sun.png");
	addTexture("board", "textures\\board.png");
	addTexture("shovel", "textures\\shovel.png");
	addTexture("shovel2", "textures\\shovel2.png");
	addTexture("frame_icon", "textures\\frame_icon.png");
}

// �������, �������
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