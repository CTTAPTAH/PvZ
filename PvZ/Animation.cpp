#include "Animation.h"
#include <iostream>

// конструкторы, деструкторы
Animation::Animation(sf::Texture* texture_, int frame_width_, int frame_height_, int count_frame_, double frametime_, sf::Vector2i position)
	: sprite(),
	texture(texture_),
	frame_width(frame_width_),
	frame_height(frame_height_),
	cur_frame(0),
	count_frame(count_frame_),
	frametime(frametime_),
	timer(0)
{
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		sprite.setPosition(position.x, position.y); // Устанавливаем позицию спрайта;
		sprite.setTextureRect(sf::IntRect(0, 0, frame_width, frame_height));
	}
}
Animation::Animation(sf::Texture* texture_) // лучше не использовать. Можно только ради быстроты написания кода
	: sprite(),
	texture(texture_),
	frame_width(50),
	frame_height(50),
	cur_frame(0),
	count_frame(5),
	frametime(0.085),
	timer(0)
{
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		sprite.setPosition(0, 0); // Устанавливаем позицию спрайта
		sprite.setTextureRect(sf::IntRect(0, 0, frame_width, frame_height));
	}
}
Animation::Animation()
	: sprite(),
	texture(nullptr),
	frame_width(100),
	frame_height(100),
	cur_frame(0),
	count_frame(1),
	frametime(0.085),
	timer(0)
{
	sprite.setTextureRect(sf::IntRect(0, 0, frame_width, frame_height));
}
Animation::Animation(const Animation& other)
{
	texture = other.texture;
	frame_width = other.frame_width;
	frame_height = other.frame_height;
	cur_frame = other.cur_frame;
	count_frame = other.count_frame;
	frametime = other.frametime;
	timer = other.timer;
	sprite = other.sprite;

	if (texture) {
		sprite.setTexture(*texture);
	}
}

// методы
void Animation::update(double dt)
{
	if (!texture) return;

	timer += dt;
	if (timer >= frametime) {
		timer -= frametime;
		cur_frame = (cur_frame + 1) % count_frame;
		sprite.setTextureRect(sf::IntRect(cur_frame * frame_width, 0, frame_width, frame_height));
	}
}
void Animation::draw(sf::RenderWindow& win)
{ 
	win.draw(sprite);
}

// геттеры, сеттеры
void Animation::setTexture(sf::Texture* texture_)
{
	texture = texture_;
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		cur_frame = 0;
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y); // Устанавливаем позицию спрайта
	}
}
void Animation::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}
void Animation::setScale(float x, float y)
{
	sprite.setScale(x, y);
}

void Animation::setFrameSize(int frame_w, int frame_h)
{
	frame_width = frame_w;
	frame_height = frame_h;
}
sf::Vector2i Animation::getRectPos() {
	return { (int)sprite.getPosition().x, (int)sprite.getPosition().y };
}

