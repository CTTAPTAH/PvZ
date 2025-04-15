#include "Chomper.h"

Chomper::Chomper(){}

Chomper::Chomper(int idx_line, sf::Vector2f pos):
	GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("chomper"),
			Config::CHOMPER_FRAME_WIDTH,
			Config::CHOMPER_FRAME_HEIGHT,
			Config::CHOMPER_FRAME_COUNT,
			Config::CHOMPER_FRAME_TIME,
			pos
	),
	{pos.x, pos.y, Config::CHOMPER_FRAME_WIDTH, Config::CHOMPER_FRAME_HEIGHT },
	Config::CHOMPER_HP,
	idx_line,
	TypeObject::PLANT,
	TypeEntity::CHOMPER
	),
	chewing_zombie_timer (time_to_chew_zombie)
{
}

Chomper::~Chomper()
{
	//std::cout << "Чомпер умер" << std::endl;
}

void Chomper::draw(sf::RenderWindow& win)
{
	animation.draw(win);
}

void Chomper::receiveMsg(Message* msg)
{
	Manager* MGR = Manager::getBorn();
	if (msg->type == TypeMsg::DAMAGE && this == msg->damage.who_receive) {
		hp -= msg->damage.damage;
		if (hp <= 0) {
			Message msg;
			msg.type = TypeMsg::DEATH;
			msg.death.creature = this;
			MGR->addMessage(msg);
			sf::Vector2f vect = MGR->getMap().getFieldIdx({ rect.left, rect.top });
			MGR->getMap().setIsPlaced(vect.x, vect.y, false);
		}
	}
}
void Chomper::update(double dt, sf::RenderWindow& win)
{
	draw(win);
	animation.update(dt);
	EatingZombie1(dt);
}

void Chomper::EatingZombie1(double dt) {

	if(!victim) victim = CollisionWithZombie();	

	if (victim and !victim->getIsDead()) {

		animation.setCountFrame(Config::CHOMPER_EAT_FRAME_COUNT);
		animation.setCurFrame(0);
		animation.setTexture(LoadTexture::getBorn().getTexture("chew"));

		isEating = true;

		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = victim;
		Manager::getBorn()->addMessage(msg);

	/*	victim->setDead(true);*/

	}
	if (victim and isEating) {

		chewing_zombie_timer -= dt;
		std::cout << chewing_zombie_timer << std::endl;

		if (chewing_zombie_timer <= 0) {

			chewing_zombie_timer = time_to_chew_zombie;

			victim = nullptr;

			isEating = false;

			animation.setTexture(LoadTexture::getBorn().getTexture("chomper"));
			animation.setCountFrame(Config::CHOMPER_FRAME_COUNT);
			animation.setCurFrame(0);
		}
	}

}

//void Chomper::EatingZombie(double dt, GameObject* object)
//{
//	Manager* MGR = Manager::getBorn();
//
//	Zombie* zombie = static_cast<Zombie*>(object);
//
//	if (!isEating) {
//		isEating = true;
//		zombie->setDead(true);
//		zombie->setVictim();
//		animation.setCountFrame(Config::CHOMPER_EAT_FRAME_COUNT);
//		animation.setCurFrame(0);
//		animation.setTexture(LoadTexture::getBorn().getTexture("chew"));
//	}
//	if (isEating) {
//
//		chewing_zombie_timer -= dt;
//
//		if (chewing_zombie_timer <= 0) {
//
//			Message msg;
//			msg.type = TypeMsg::DEATH;
//			msg.death.creature = zombie;
//			MGR->addMessage(msg);
//
//			chewing_zombie_timer = time_to_chew_zombie;
//			isEating = false;
//			animation.setTexture(LoadTexture::getBorn().getTexture("chomper"));
//			animation.setCountFrame(Config::CHOMPER_FRAME_COUNT);
//			animation.setCurFrame(0);
//		}
//	}
//}

GameObject* Chomper::CollisionWithZombie()
{

	auto objects = Manager::getBorn()->getListObject();

	for (auto elem : objects) {
		if (elem->getTypeObj() == TypeObject::ZOMBIE and elem->getIdxLine() == idx_line) {

			if (elem->getRect().left <= rect.left + rect.width + 20) {
				/*Zombie* zombie = static_cast<Zombie*>(elem);*/
				return elem;
			}
		}
	}
	return nullptr;
}

bool Chomper::getIsEating()
{
	return isEating;
}
