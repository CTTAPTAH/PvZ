#include "Projectile.h"

Projectile::Projectile()
{
	pos.x = 0; pos.y = 0;
}
Projectile::Projectile(Position pos_, sf::IntRect rect_,
	sf::Color color_)
{
	pos = pos_;
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
}
void Projectile::sendMsg()
{

}
void Projectile::receiveMsg()
{

}