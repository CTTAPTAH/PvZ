#include "Peashooter.h"

// конструкторы, деструкторы
Peashooter::Peashooter()
    : Peashooter({ 0, 0 }, 0)
{
}
Peashooter::Peashooter(sf::Vector2i pos, int idx_line_)
    : GameObject(
        Animation(LoadTexture::getBorn().getTexture("peashooter"),
            Config::PEASHOOTER_FRAME_WIDTH,
            Config::PEASHOOTER_FRAME_HEIGHT,
            Config::PEASHOOTER_COUNT_FRAME,
            Config::PEASHOOTER_FRAMETIME,
            pos
        ),
        { pos.x, pos.y, Config::PEASHOOTER_FRAME_WIDTH, Config::PEASHOOTER_FRAME_HEIGHT },
        Config::PEASHOOTER_HP,
        idx_line_,
        TypeObject::PLANT
    ),
    is_shooting(false),
    damage(Config::PEASHOOTER_DAMAGE),
    time_reload(Config::PEASHOOTER_TIME_RELOAD),
    reload(0)
{
    animation.setPosition(rect.left, rect.top);
}

// методы
void Peashooter::update(double dt, sf::RenderWindow& win)
{
    isShooting(dt);
    animation.update(dt);
    draw(win);
}
void Peashooter::isShooting(double dt)
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

            sf::IntRect rect_projectile(
                rect.left + Config::PEASHOOTER_PROJECTILE_OFFSET_X,
                rect.top + Config::PEASHOOTER_PROJECTILE_OFFSET_Y,
                Config::PEA_PROJECTILE_FRAME_WIDTH,
                Config::PEA_PROJECTILE_FRAME_HEIGHT
            );
            msg.create.new_object = new PeaProjectile(rect_projectile, idx_line, damage);
            manager->addMessage(msg);
        }
    }
}
void Peashooter::draw(sf::RenderWindow& win) {
    animation.draw(win);
}
void Peashooter::receiveMsg(Message* msg)
{
    Manager* mng = Manager::getBorn();
    if (msg->type == TypeMsg::DAMAGE and this == msg->damage.who_receive) {
        hp -= msg->damage.damage;
        if (hp <= 0) {
            Message msg;
            msg.type = TypeMsg::DEATH;
            msg.death.creature = this;
            mng->addMessage(msg);
        }
    }
}

// геттеры, сеттеры
void Peashooter::setRect(sf::IntRect rect_)
{
    rect = rect_;
    animation.setPosition(rect.left, rect.top);
}