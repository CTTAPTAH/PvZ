#include "Animation.h"

Animation::Animation(sf::Texture* texture_, int frame_width_, int frame_height_, int count_frame_, double frametime_)
{
	texture = texture_;
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		sprite.setPosition(0, 0); // Устанавливаем позицию спрайта
	}
	frame_width = frame_width_;
	frame_height = frame_height_;
	cur_frame = 0;
	count_frame = count_frame_;
	frametime = frametime_;
	timer = 0;
}
Animation::Animation(sf::Texture* texture_)
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
Animation::Animation()
{
	texture = nullptr;
	frame_width = frame_height = 100;
	cur_frame = 0;
	count_frame = 28;//Кадров 36 но спрайт кривой, надо придумать как поправить
	frametime = 0.055;
	timer = 0;
}
void Animation::update(double dt)
{
	timer += dt;
	if (timer >= frametime) {
		timer -= frametime;
		cur_frame = (cur_frame + 1) % count_frame;
		sprite.setTextureRect(sf::IntRect(cur_frame * frame_width, 0, frame_width, frame_height));
	}

//	if (texture)
//		printf_s("dt: %6.4lf\ntimer: %4.2lf\nframe_width: %d\n\
//frame_height: %d\ncur_frame: %d\ncount_frame: %d\n\
//frametime: %4.2lf\n\
//-----------------------\n",
//			dt, timer, frame_width, frame_height, cur_frame,
//			count_frame, frametime);
}
void Animation::draw(sf::RenderWindow& win)
{ 
	win.draw(sprite);
}
void Animation::setTexture(sf::Texture* texture_)
{
	texture = texture_;
	if (texture) { // Проверяем, загружена ли текстура
		sprite.setTexture(*texture);
		sprite.setPosition(0, 0); // Устанавливаем позицию спрайта
	}
}
void Animation::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}
void Animation::setScale(double x, double y)
{
	sprite.setScale(x, y);
}
