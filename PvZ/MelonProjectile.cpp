#include "MelonProjectile.h"

// конструкторы, деструкторы
MelonProjectile::MelonProjectile()
	: MelonProjectile( {0, 0}, 0, 0.0)
{
}
MelonProjectile::MelonProjectile(sf::Vector2f pos_, int idx_line_, double vx_)
	: GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("melon_projectile"),
			Config::MELON_FRAME_WIDTH,
			Config::MELON_FRAME_HEIGHT,
			Config::MELON_COUNT_FRAME,
			Config::MELON_FRAMETIME,
			pos_
		),
		{ pos_.x, pos_.y, Config::MELON_FRAME_WIDTH, Config::MELON_FRAME_HEIGHT },
		Config::MELON_HP,
		idx_line_,
		TypeObject::PROJECTILE,
		TypeEntity::MELON_PROJECTILE
	),
	pos({ float(pos_.x), float(pos_.y) }),
	vx(vx_),
	vy(Config::MELON_VY),
	damage(Config::MELONPULT_DAMAGE)
{
}

// методы
void MelonProjectile::update(double dt, sf::RenderWindow& win)
{
	move(dt);
	collisionWithZombies();
	checkOutOfBounds();
	draw(win);
}
void MelonProjectile::move(double dt)
{
	pos.x += vx * dt;
	pos.y += vy * dt;
	vy += Config::MELON_GRAVITY * dt;
	setRect({ pos.x, pos.y, rect.width, rect.height });
}
void MelonProjectile::draw(sf::RenderWindow& win)
{
	animation.draw(win);
	// Создаем квадрат
	sf::RectangleShape square(sf::Vector2f(5.f, 5.f));

	// Устанавливаем позицию квадрата (необязательно)
	square.setPosition(float(rect.left), float(rect.top));

	// Устанавливаем цвет заливки (необязательно)
	square.setFillColor(sf::Color::Red);

	win.draw(square);
}
void MelonProjectile::checkOutOfBounds()
{
	Manager* mng = Manager::getBorn();
	if (rect.left + rect.width < 0 or rect.left > mng->getWinWidth() or
		rect.top > mng->getWinHeight()) {
		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;

		mng->addMessage(msg);
	}
}
void MelonProjectile::collisionWithZombies()
{
	Manager* mng = Manager::getBorn();
	std::list<GameObject*> objects = mng->getListObject();
	for (auto& zombie : objects) {
		if (zombie->getTypeObj() == TypeObject::ZOMBIE and
			zombie->getIdxLine() == idx_line) {
			if (rect.intersects(zombie->getRect())) {
				// удаляем снаряд
				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = this;
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
void MelonProjectile::receiveMsg(Message* msg)
{
}

//геттеры, сеттеры