#include "Peashooter.h"
#include "Message.h"

Peashooter::Peashooter(Position pos_, int hp_, int idx_line_, TypeObject type_)
    : GameObject(pos_, hp_, idx_line_, type_)
{
    // временно место текстуры
    rect.left = 0; rect.top = 0; rect.width = 50; rect.height = 50;
    color.r = 0; color.g = 255; color.b = 0; color.a = 0;
    // То, что было
    reload = time_reload; 
}

void Peashooter::isShooting(double dt)
{
    reload -= dt;
    if (reload <= 0) {
        reload = time_reload;

        Message msg;
        msg.type = TypeMsg::CREATE;

        Position pos_projectile{ pos.x, pos.y }; // Заменить на норм спавн
        sf::IntRect rect_projectile{ (int)pos.x + 25,
            (int)pos.y + 25,
            10,
            10}; // Заменить на указываемые
        sf::Color color(0, 0, 255, 255);

        msg.create.new_object = new Projectile(pos_projectile,
            rect_projectile, color);
        Manager* manager = Manager::GetBorn();
        manager->addMessage(msg);
    }
}
void Peashooter::Update(double dt)
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