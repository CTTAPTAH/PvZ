#include "NewspaperZombie.h"

NewspaperZombie::NewspaperZombie(int idx_line, int frame_w, int frame_h) :
	Zombie(idx_line, frame_w, frame_h)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("newszombie"));
	hp = 6;
	type_ent = TypeEntity::NEWSPAPER_ZOMBIE;
}

NewspaperZombie::~NewspaperZombie()
{}

void NewspaperZombie::move(double dt)
{
	if (!victim) {
		if (isHavePaper) {
			rect.left -= velocity_x * dt;
		}
		else {
			rect.left -= (velocity_x * 2.0f) * dt;
		}
		animation.setPosition(rect.left, rect.top);
	}
}
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
