#include "Animation.h"

// конструкторы, деструкторы
Animation::Animation(sf::Texture* texture_, int frame_width_, int frame_height_, int count_frame_, double frametime_, sf::Vector2i position) : sprite()
{
	texture = texture_;
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		sprite.setPosition(position.x, position.y); // Устанавливаем позицию спрайта
	}
	frame_width = frame_width_;
	frame_height = frame_height_;
	cur_frame = 0;
	count_frame = count_frame_;
	frametime = frametime_;
	timer = 0;
}
Animation::Animation(sf::Texture* texture_) : sprite()
{
	texture = texture_;
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		sprite.setPosition(0, 0); // Устанавливаем позицию спрайта
	}
	frame_width = frame_height = 100;
	cur_frame = 0;
	count_frame = 36;
	frametime = 0.085;
	timer = 0;
}
Animation::Animation() : sprite()
{
	texture = nullptr;
	frame_width = frame_height = 100;
	cur_frame = 0;
	count_frame = 28;//Кадров 36 но спрайт кривой, надо придумать как поправить
	frametime = 0.055;
	timer = 0;
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
		sprite.setPosition(0, 0); // Устанавливаем позицию спрайта
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