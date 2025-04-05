#include "PeaProjectile.h"

// конструкторы, деструкторы
PeaProjectile::PeaProjectile()
	: PeaProjectile(
		{ 0, 0 },
		0,
		0)
{
	
}
PeaProjectile::PeaProjectile(sf::Vector2i vect, int idx_line_, double damage_)
	: GameObject(
		Animation(LoadTexture::getBorn().getTexture("pea_projectile"),
			Config::PEA_PROJECTILE_FRAME_WIDTH,
			Config::PEA_PROJECTILE_FRAME_HEIGHT,
			Config::PEA_PROJECTILE_COUNT_FRAME,
			Config::PEA_PROJECTILE_FRAMETIME,
			vect
		),
		{ vect.x, vect.y, Config::PEA_PROJECTILE_FRAME_WIDTH, Config::PEA_PROJECTILE_FRAME_HEIGHT },
		Config::PEA_PROJECTILE_HP,
		idx_line_,
		TypeObject::PROJECTILE,
		TypeEntity::PEA_PROJECTILE
	),
	speed(Config::PEA_PROJECTILE_SPEED),
	damage(damage_),
	is_dead(false)
{
}

// методы
void PeaProjectile::update(double dt, sf::RenderWindow& win)
{
	move(dt);
	if (!is_dead) collisionWithZombies();
	if (!is_dead) checkOutOfBounds();
	draw(win);
}
void PeaProjectile::move(double dt)
{
	rect.left += speed * dt;
	animation.setPosition(rect.left, rect.top);
}
void PeaProjectile::draw(sf::RenderWindow& win)
{
	animation.draw(win);
}
void PeaProjectile::checkOutOfBounds()
{
	Manager* mng = Manager::getBorn();
	if (rect.left + rect.width < 0 or rect.left > mng->getWinWidth() or
		rect.top + rect.height < 0 or rect.top > mng->getWinHeight()) {
		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;
		is_dead = true;

		mng->addMessage(msg);
	}
}
void PeaProjectile::collisionWithZombies()
{
	Manager* mng = Manager::getBorn();
	std::list<GameObject*> objects = mng->getListObject();
	for (auto& zombie : objects) {
		if (zombie->getTypeObj() == TypeObject::ZOMBIE) {
			if (rect.intersects(zombie->getRect())) {
				// удаляем снаряд
				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = this;
				is_dead = true;
				mng->addMessage(msg);

				// наносим урон зомби
				Message msg2;
				msg2.type = TypeMsg::DAMAGE;
				msg2.damage.damage = damage;
				msg2.damage.who_receive = zombie;
				mng->addMessage(msg2);
				break;
			}
		}
	}
}
void PeaProjectile::receiveMsg(Message* msg)
{
}

// геттеры, сеттеры
void PeaProjectile::setRect(sf::IntRect rect_)
{
	rect = rect_;
	animation.setPosition(rect.left, rect.top);
}