#include "LoadTexture.h"

<<<<<<< HEAD
LoadTexture::LoadTexture() {
	LoadAllTextures();
}
LoadTexture::LoadTexture(const LoadTexture&) {}
LoadTexture::~LoadTexture() {}
=======
// ������������, ����������
>>>>>>> Добавлено:

// ������
LoadTexture& LoadTexture::getBorn()
{
	static LoadTexture born;
	return born;
}
void LoadTexture::addTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "������ �������� �������: �� ������� ��������� ��������" << std::endl;
		return;
	}
<<<<<<< HEAD
	return true;
}
bool LoadTexture::addTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;

	if (!loadFromFile(texture, filename)) {
		return false; // ������ �������� ��������
	}

	textures[name] = std::move(texture); // ����������, � �� ��������.
	// � sf::Texture ��� ������������ �����������

	return true;
}

void LoadTexture::LoadAllTextures(){
	addTexture("peashooter", "texture\\peashooter.png");
	addTexture("sun", "texture\\sun.png");
	addTexture("sunflower", "texture\\Sunflower.png");
	addTexture("zombie", "texture\\\zomsheet.png");
	addTexture("car", "texture\\Machine.png");
}

const std::map<std::string, sf::Texture>&LoadTexture::GetTexturesList() const {
	return textures;
}

=======

	textures[name] = std::move(texture); // ����������, �.�. ���
	// ������������ �����������
}
void LoadTexture::loadAllTexture()
{
	addTexture("peashooter", "textures\\peashooter.png");
	addTexture("map", "textures\\map.png");
	addTexture("pea_projectile", "textures\\pea_projectile.png");
}

// �������, �������
sf::Texture* LoadTexture::getTexture(const std::string& name)
{
	auto it = textures.find(name);
	return (it != textures.end()) ? &it->second : nullptr;
}
>>>>>>> Добавлено:
