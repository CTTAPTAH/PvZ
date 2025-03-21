#include "LoadTexture.h"

<<<<<<< HEAD
LoadTexture::LoadTexture() {
	LoadAllTextures();
}
LoadTexture::LoadTexture(const LoadTexture&) {}
LoadTexture::~LoadTexture() {}
=======
// конструкторы, деструктор
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:

// методы
LoadTexture& LoadTexture::getBorn()
{
	static LoadTexture born;
	return born;
}
void LoadTexture::addTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "Ошибка загрузки текстур: не удалось загрузить текстуру" << std::endl;
		return;
	}
<<<<<<< HEAD
	return true;
}
bool LoadTexture::addTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;

	if (!loadFromFile(texture, filename)) {
		return false; // Ошибка загрузки текстуры
	}

	textures[name] = std::move(texture); // перемещаем, а не копируем.
	// У sf::Texture нет конструктора копирования

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

	textures[name] = std::move(texture); // перемещаем, т.к. нет
	// конструктора копирования
}
void LoadTexture::loadAllTexture()
{
	addTexture("peashooter", "textures\\peashooter.png");
	addTexture("map", "textures\\map.png");
	addTexture("pea_projectile", "textures\\pea_projectile.png");
}

// геттеры, сеттеры
sf::Texture* LoadTexture::getTexture(const std::string& name)
{
	auto it = textures.find(name);
	return (it != textures.end()) ? &it->second : nullptr;
}
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:
