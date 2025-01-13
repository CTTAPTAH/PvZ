#include "Projectile.h"

Projectile::Projectile()
{
	pos.x = 0; pos.y = 0;
}
Projectile::Projectile(sf::IntRect rect_, sf::Color color_)
{
	rect = rect_;
	color = color_;
}
void Projectile::move(double dt)
{
	rect.left += speed * dt;
}
void Projectile::draw(sf::RenderWindow& win)
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(rect.left, rect.top);
	rectangle.setSize(sf::Vector2f(rect.width, rect.height));
	rectangle.setFillColor(color);
	win.draw(rectangle);
}
void Projectile::update(double dt, sf::RenderWindow& win)
{
	move(dt);
	collision();
	draw(win);
}
void Projectile::collision()
{
	if (rect.left + rect.width < 0 or rect.left > win_width or
		rect.top + rect.height < 0 or rect.top > win_height) {
		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;

		Manager* mng = Manager::GetBorn();
		mng->addMessage(msg);
	}
}
void Projectile::sendMsg()
{

}
void Projectile::receiveMsg()
{

}