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
	addTexture("peashooter", "textures\\peashooter.png");
	addTexture("map", "textures\\map.png");
	addTexture("pea_projectile", "textures\\pea_projectile.png");
	addTexture("car", "textures\\Machine.png");
	addTexture("sun", "textures\\sun.png");
	addTexture("sunflower", "textures\\Sunflower.png");
	addTexture("zombie", "textures\\zomsheet.png");
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