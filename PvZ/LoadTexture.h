#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
#include"Message.h"

class LoadTexture
{
private:
	std::map<std::string, sf::Texture> textures;

	// ������������, ����������
	LoadTexture() = default;
	~LoadTexture() = default;
	LoadTexture(const LoadTexture&) = delete;
	LoadTexture& operator=(const LoadTexture&) = delete;
public:
	// ������
	void addTexture(const std::string& name, const std::string& filename);
	void loadAllTexture();

	// �������, �������
	static LoadTexture& getBorn();
	sf::Texture* getTexture(const std::string& name);
};