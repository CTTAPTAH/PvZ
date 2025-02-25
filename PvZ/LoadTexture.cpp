#include "LoadTexture.h"

LoadTexture::LoadTexture() {}
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