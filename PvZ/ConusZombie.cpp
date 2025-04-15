#include "ConusZombie.h"

// конструкторы, декструкторы
ConusZombie::ConusZombie(int idx_line)
	: Zombie(idx_line,
		Config::CONUS_ZOMBIE_FRAME_WIDTH,
		Config::CONUS_ZOMBIE_FRAME_HEIGHT
	)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("conus_zombie1"));
	rect.width = Config::CONUS_ZOMBIE_FRAME_WIDTH;
	rect.height = Config::CONUS_ZOMBIE_FRAME_HEIGHT;
	hp = Config::CONUS_ZOMBIE_HP;
	type_ent = TypeEntity::CONUS_ZOMBIE;
}

// методы
void ConusZombie::receiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::DEATH and msg->death.creature->getTypeObj() == TypeObject::PLANT) {
		if (victim == msg->death.creature) {
			victim = nullptr;
		}
	}

	if (msg->type == TypeMsg::DAMAGE and
		this == msg->damage.who_receive) {
		hp -= msg->damage.damage;
		
		if (Config::CONUS_ZOMBIE_HP * 2 / 4 < hp and hp <= Config::CONUS_ZOMBIE_HP * 3 / 4) {
			animation.setTexture(LoadTexture::getBorn().getTexture("conus_zombie2"));
		}
		else if (Config::CONUS_ZOMBIE_HP * 1 / 4 < hp and hp <= Config::CONUS_ZOMBIE_HP * 2 / 4) {
			animation.setTexture(LoadTexture::getBorn().getTexture("conus_zombie3"));
		}
		else if (hp <= Config::CONUS_ZOMBIE_HP * 1 / 4) {
			animation.setTexture(LoadTexture::getBorn().getTexture("zombie"));
			rect.width = Config::ZOMBIE_FRAME_WIDTH; // вручную плохо. Config лучше
			rect.height = Config::ZOMBIE_FRAME_HEIGHT; // вручную плохо. Config лучше
			animation.setFrameSize(rect.width, rect.height);
		}

		if (hp <= 0) {
			Message msg;
			msg.type = TypeMsg::DEATH;
			msg.death.creature = this;
			Manager* MGR = Manager::getBorn();
			MGR->addMessage(msg);
		}
	}
}