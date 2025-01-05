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
public:
	LoadTexture();
	LoadTexture(const LoadTexture&);
	~LoadTexture();
	sf::Texture* LoadingRecieveMSG(Message* msg);
	sf::Texture* LoadingRecieveMSG1(sf::Texture* texture, sf::IntRect rect, const std::string filename);
};
