#include "SnowPeaProjectile.h"

SnowPeaProjectile::SnowPeaProjectile(sf::Vector2f vect, int idx_line_, double damage_):
	PeaProjectile(vect, idx_line_, damage_)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("snowpeaPr"));
	TypeEntity::SNOW_PEA_PROJECTILE;
}

SnowPeaProjectile::~SnowPeaProjectile()
{
}
void SnowPeaProjectile::collisionWithZombies()
{
	Manager* mng = Manager::getBorn();
	std::list<GameObject*> objects = mng->getListObject();
	for (auto& zombie : objects) {
		if (zombie->getTypeObj() == TypeObject::ZOMBIE) {
			if (rect.intersects(zombie->getRect())) {

				Zombie* current_zombie = static_cast<Zombie*>(zombie);
				current_zombie->setHaveFrozenEffect(true);
				current_zombie->setZombieFrozenNull();

				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = this;
				is_dead = true;
				mng->addMessage(msg);


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
