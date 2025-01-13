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
sf::Texture* LoadTexture::LoadingRecieveMSG1(sf::Texture* texture, sf::IntRect rect, const std::string filename) {
	if (!texture->loadFromFile(filename, rect)) {
		std::cout << "Ошибка загрузки текстуры!" << std::endl;
		return nullptr;
	}
	return texture;
}