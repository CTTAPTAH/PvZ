#include "DiscoZombie.h"

// конструкторы, декструкторы
DiscoZombie::DiscoZombie(int idx_line)
	: Zombie(idx_line,
		Config::DISCO_ZOMBIE_FRAME_WIDTH,
		Config::DISCO_ZOMBIE_FRAME_HEIGHT
	),
	hasSpawned(false)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("disco_zombie"));
	rect.width = Config::DISCO_ZOMBIE_FRAME_WIDTH;
	rect.height = Config::DISCO_ZOMBIE_FRAME_HEIGHT;
	hp = Config::DEFAULT_ZOMBIE_HP;
	type_ent = TypeEntity::DISCO_ZOMBIE;
}

void DiscoZombie::move(double dt)
{
	if (!victim) { // добавил условие
		rect.left -= velocity_x * dt;
		animation.setPosition(rect.left, rect.top);
	}

	if (!hasSpawned and
		rect.left <= Manager::getBorn()->getWinWidth() / 2 + 100) {
		hasSpawned = true;

		Manager* mng = Manager::getBorn();
		Message msg;
		msg.type = TypeMsg::CREATE;

		// слева
		Zombie* zm_left = new Zombie(idx_line, 63, 100);
		zm_left->setRect({
			rect.left - Config::DISCO_ZOMBIE_SPAWN_LEFT_OFFSET,
			zm_left->getRect().top,
			63,
			100
			}
		);
		msg.create.new_object = zm_left;
		mng->addMessage(msg);

		// справа
		Zombie* zm_right = new Zombie(idx_line, 63, 100);
		zm_right->setRect({
			rect.left + Config::DISCO_ZOMBIE_SPAWN_RIGHT_OFFSET,
			zm_right->getRect().top,
			63,
			100
			}
		);
		msg.create.new_object = zm_right;
		mng->addMessage(msg);

		// сверху
		if (idx_line != 0) {
			Zombie* zm_up = new Zombie(idx_line - 1, 63, 100);
			zm_up->setRect({
				rect.left,
				zm_up->getRect().top,
				63,
				100
				}
			);
			msg.create.new_object = zm_up;
			mng->addMessage(msg);
		}

		// снизу
		if (idx_line != 4) {
			Zombie* zm_down = new Zombie(idx_line + 1, 63, 100);
			zm_down->setRect({
				rect.left,
				zm_down->getRect().top,
				63,
				100
				}
			);
			msg.create.new_object = zm_down;
			mng->addMessage(msg);
		}
	}
}