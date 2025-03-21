#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
#include"Message.h"

<<<<<<< HEAD

enum class Identificate {
	PEA,
	ZOMBIE,
	FONT
};

=======
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:
class LoadTexture
{
private:
	std::map<std::string, sf::Texture> textures;
<<<<<<< HEAD
public:
	LoadTexture();
	LoadTexture(const LoadTexture&);
	~LoadTexture();
	/*sf::Texture* LoadingRecieveMSG(Message* msg);*/
	static bool loadFromFile(sf::Texture& texture,  const std::string& filename);
	void LoadAllTextures();
	bool addTexture(const std::string& name, const std::string& filename);
	const std::map<std::string, sf::Texture>& GetTexturesList() const;
};
=======

	// конструктор, деструктор
	LoadTexture() = default;
	~LoadTexture() = default;
	LoadTexture(const LoadTexture&) = delete;
	LoadTexture& operator=(const LoadTexture&) = delete;
public:
	// методы
	static LoadTexture& getBorn();
	void addTexture(const std::string& name, const std::string& filename);
	void loadAllTexture();

	// геттеры, сеттеры
	sf::Texture* getTexture(const std::string& name);

};
>>>>>>> Р”РѕР±Р°РІР»РµРЅРѕ:
