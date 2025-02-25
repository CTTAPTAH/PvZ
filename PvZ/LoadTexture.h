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
public:

	LoadTexture();
	LoadTexture(const LoadTexture&);
	~LoadTexture();
	sf::Texture* LoadingRecieveMSG(Message* msg);
	static bool loadFromFile(sf::Texture& texture,  const std::string& filename);
};
