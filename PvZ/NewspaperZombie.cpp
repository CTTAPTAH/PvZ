#include "NewspaperZombie.h"

NewspaperZombie::NewspaperZombie(int idx_line, int frame_w, int frame_h) :
	Zombie(idx_line, frame_w, frame_h)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("newszombie"));
	hp = 6;
}

NewspaperZombie::~NewspaperZombie()
{}
void NewspaperZombie::receiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::DEATH && msg->death.creature->getTypeObj() == TypeObject::PLANT) {
		if (victim == msg->death.creature) {
			victim = nullptr;
		}
	}
	if (msg->type == TypeMsg::DAMAGE and
		this == msg->damage.who_receive) {
		hp -= msg->damage.damage;

		if (hp <= 3) {
			isHavePaper = false;
			velocity_x = Config::NEWSPAPER_ZOMBIE_DOUBLE_SPEED;
			animation.setTexture(LoadTexture::getBorn().getTexture("wnewszombie"));
			damage = 2;
		}
		if(hp<=0){
			Message msg;
			msg.type = TypeMsg::DEATH;
			msg.death.creature = this;
			Manager* MGR = Manager::getBorn();
			MGR->addMessage(msg);
		}
	}
}