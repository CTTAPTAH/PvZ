#include "Peashooter.h"
#include "Message.h"

Peashooter::Peashooter(int idx_line_, TypeObject type_)
    : GameObject(idx_line_, type_)
{
    // временно место текстуры
    rect.left = 0; rect.top = 0; rect.width = 50; rect.height = 50;
    color.r = 0; color.g = 255; color.b = 0; color.a = 0;
    // То, что было
    reload = time_reload; 
}
Peashooter::Peashooter()
{
    rect.left = 0; rect.top = 0; rect.width = 50; rect.height = 50;
    color.r = 0; color.g = 255; color.b = 0; color.a = 0;
    reload = time_reload;
    idx_line = -1; type = TypeObject::PEASHOOTER;
}

void Peashooter::isShooting(double dt)
{
    Manager* manager = Manager::GetBorn();

    if (!shooting and manager->getZombieOnLine(idx_line) > 0) {
        shooting = true;
        reload = time_reload;
    }

    if (shooting) {
        if (manager->getZombieOnLine(idx_line) == 0) {
            shooting = false;
            reload = time_reload;
            return;
        }

        reload -= dt;
        if (reload <= 0) {
            reload = time_reload;

            Message msg;
            msg.type = TypeMsg::CREATE;

            Position pos_projectile{ pos.x, pos.y }; // Заменить на норм спавн
            sf::IntRect rect_projectile{ (int)pos.x + 25,
                (int)pos.y + 25,
                10,
                10 }; // Заменить на указываемые
            sf::Color color(0, 0, 255, 255);

            msg.create.new_object = new Projectile(rect_projectile, color);
            manager->addMessage(msg);
        }
    }
}
void Peashooter::update(double dt, sf::RenderWindow& win)
{
    isShooting(dt);
}
void Peashooter::setPosition(Position pos_)
{
    pos = pos_;
}
void Peashooter::setRect(sf::IntRect rect_)
{
    rect = rect_;
}
void Peashooter::setColor(sf::Color color_)
{
    color = color_;
}