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
		
		if (hp == 6 or hp == 5) {
			animation.setTexture(LoadTexture::getBorn().getTexture("conus_zombie2"));
		}
		else if (hp == 4 or hp == 3) {
			animation.setTexture(LoadTexture::getBorn().getTexture("conus_zombie3"));
		}
		else if (hp == 2 or hp == 1) {
			animation.setTexture(LoadTexture::getBorn().getTexture("zombie"));
			rect.width = 63; // вручную плохо. Config лучше
			rect.height = 100; // вручную плохо. Config лучше
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