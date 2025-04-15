#include "Melonpult.h"
#include "MelonProjectile.h"

// конструкторы, деструкторы
Melonpult::Melonpult()
    : Melonpult({ 0, 0 }, 0)
{
}
Melonpult::Melonpult(sf::Vector2f pos, int idx_line_)
	: Peashooter(
        pos, idx_line_
    ),
    is_shooting(false),
    damage(Config::MELONPULT_DAMAGE),
    time_reload(Config::MELONPULT_TIME_RELOAD),
    reload(Config::MELONPULT_TIME_RELOAD)
{
    damage = Config::MELONPULT_DAMAGE;
    time_reload = Config::MELONPULT_TIME_RELOAD;
    animation = Animation(LoadTexture::getBorn().getTexture("melonpult"),
        Config::MELONPULT_FRAME_WIDTH,
        Config::MELONPULT_FRAME_HEIGHT,
        Config::MELONPULT_COUNT_FRAME,
        Config::MELONPULT_FRAMETIME,
        pos
    );
    rect.width = Config::MELONPULT_FRAME_WIDTH;
    rect.height = Config::MELONPULT_FRAME_HEIGHT;
    hp = Config::MELONPULT_HP;
    type_obj = TypeObject::PLANT;
    type_ent = TypeEntity::MELLONPULT;
}

// методы
void Melonpult::isShooting(double dt)
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

            // Создаём снаряд. Для это находим vx
            // Позиции
            sf::Vector2f pos_projectile = {
                rect.left + Config::MELON_PROJECTILE_OFFSET_Y,
                rect.top + Config::MELON_PROJECTILE_OFFSET_Y
            };

            // Ищем координату цели
            // Получаем позицию ближайшего зомби
            int coord_zm_x = 10000;
            int coord_zm_y = 0;
            double zm_speed = 0;
            for (const auto& obj : manager->getListObject()) {
                if (obj and
                    obj->getTypeObj() == TypeObject::ZOMBIE and
                    obj->getIdxLine() == idx_line and
                    obj->getRect().left < coord_zm_x) {

                    coord_zm_x = obj->getRect().left;
                    coord_zm_y = obj->getRect().top;
                    
                    // Приводим к классу зомби и получаем скорость
                    Zombie* zm = dynamic_cast<Zombie*>(obj);
                    if (zm) {
                        zm_speed = zm->getSpeed();
                    }
                }
            }

            // Рассчитываем сам vx с учётом возвышенности

            // Начальные параметры полёта
            double vy = Config::MELON_VY;
            double g = Config::MELON_GRAVITY;

            double t_up = abs(vy) / g;
            double h_up = vy * vy / (2 * g);
            double h_down = h_up + (coord_zm_y - pos_projectile.y);
            double t_down = sqrt(2.0 * h_down / g);
            double t = t_up + t_down;
            double pred_zm_x = coord_zm_x - zm_speed * t;
            if (pred_zm_x < pos_projectile.x) { // если зомби дойдёт до растения раньше, чем долетит снаряд
                pred_zm_x = (rect.left + rect.width) + Config::ZOMBIE_FRAME_WIDTH / 4;
                // Config::ZOMBIE_FRAME_WIDTH / 4 - стреляем наперёд
            }
            double dx = pred_zm_x - pos_projectile.x;
            double vx = dx / t;

            // Создаём
            msg.create.new_object = new MelonProjectile(
                pos_projectile,
                idx_line,
                vx
            );

            manager->addMessage(msg);
        }
    }
}

// геттеры, сеттеры