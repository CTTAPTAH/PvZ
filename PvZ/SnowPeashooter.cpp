#include "SnowPeashooter.h"

SnowPeashooter::SnowPeashooter(int idx_line_, sf::Vector2i pos):
	Peashooter(pos, idx_line_)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("snowpea"));
	TypeEntity::SNOWPEASHOOTER;
}

SnowPeashooter::~SnowPeashooter()
{
}

void SnowPeashooter::isShooting(double dt)
{
    Manager* manager = Manager::getBorn();
    int zombies = manager->getZombieOnLine(idx_line);

    if (!is_shooting and zombies > 0) {
        is_shooting = true;
        reload = time_reload;
    }

    if (is_shooting) {
        if (zombies == 0) {
            is_shooting = false;
            reload = time_reload;
            return;
        }

        reload -= dt;
        if (reload <= 0) {
            reload = time_reload;

            Message msg;
            msg.type = TypeMsg::CREATE;

            sf::Vector2i vect_projectile(
                rect.left + Config::PEASHOOTER_PROJECTILE_OFFSET_X,
                rect.top + Config::PEASHOOTER_PROJECTILE_OFFSET_Y
            );
            msg.create.new_object = new SnowPeaProjectile(
                { rect.left + Config::PEASHOOTER_PROJECTILE_OFFSET_X,
                rect.top + Config::PEASHOOTER_PROJECTILE_OFFSET_Y
                },
                idx_line,
                damage
            );
            manager->addMessage(msg);
        }
    }
}