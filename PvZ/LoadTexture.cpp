#include "LoadTexture.h"

LoadTexture::LoadTexture() {
	LoadAllTextures();
}
LoadTexture::LoadTexture(const LoadTexture&) {}
LoadTexture::~LoadTexture() {}

//sf::Texture* LoadTexture::LoadingRecieveMSG(Message* msg) {
//	if (!msg->load.texture->loadFromFile(msg->load.filename, msg->load.rect)) {
//		std::cout << "Ошибка загрузки текстуры!" << std::endl;
//		return nullptr;
//	}
//	return msg->load.texture;
//}
bool LoadTexture::loadFromFile(sf::Texture& texture, const std::string& filename) {
	if (!texture.loadFromFile(filename)) {
		std::cout << "Ошибка загрузки текстуры!" << std::endl;
		return false;
	}
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

