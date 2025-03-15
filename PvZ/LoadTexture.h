#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
#include"Message.h"


enum class Identificate {
	PEA,
	ZOMBIE,
	FONT
};

class LoadTexture
{
private:
	std::map<std::string, sf::Texture> textures;
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
