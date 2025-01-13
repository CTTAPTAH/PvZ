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
	CollisionWithGO();
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

void Projectile::CollisionWithGO()
{
	//Своя коллизия:
	/*if (rect.left + rect.width > zombie_rect.left and
		rect.left < zombie_rect.left + zombie_rect.width and
		rect.top + rect.height > zombie_rect.top and
		rect.top < zombie_rect.top + zombie_rect.height) {

	}*/
	//Затестил через библиотеку
	Manager* MGR = Manager::GetBorn();
	std::list<GameObject*> objects = MGR->getListObject();
	for (auto obj : objects) {
		if (obj->getType() == TypeObject::ZOMBIE) {
			if (rect.intersects(obj->getRect())) {
				std::cout << "Обнаружена коллизия между ректами!" << std::endl;
				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = this;
				MGR->addMessage(msg);

				Message msg2;
				msg2.type = TypeMsg::DAMAGE;
				msg2.damage.damage = 1;
				msg2.damage.who_receive = obj;
				MGR->addMessage(msg2);
			}
		}
	}
}

void Projectile::sendMsg()
{

}
void Projectile::receiveMsg()
{

}