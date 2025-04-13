#include "Nut.h"

Nut::Nut(int idx_line, sf::Vector2f pos) :
	GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("nut_full_hp"),
			Config::NUT_FRAME_WIDTH,
			Config::NUT_FRAME_HEIGHT,
			Config::NUT_FRAME_COUNT,
			Config::NUT_FRAME_TIME,
			pos
		),
		{pos.x, pos.y, Config::NUT_FRAME_WIDTH, Config::NUT_FRAME_HEIGHT},
		Config::NUT_HP,
		idx_line,
		TypeObject::PLANT,
		TypeEntity::WALLNUT
	)
{
}
Nut::Nut() {}

Nut::~Nut(){}


void Nut::draw(sf::RenderWindow& win)
{
	animation.draw(win);
}

void Nut::update(double dt, sf::RenderWindow& win)
{
	animation.update(dt);
	draw(win);
}

void Nut::receiveMsg(Message* msg)
{
	Manager* mng = Manager::getBorn();
	if (msg->type == TypeMsg::DAMAGE and this == msg->damage.who_receive) {
		hp -= msg->damage.damage;

		if (hp <= 8 && hp > 4) {
			animation.setTexture(LoadTexture::getBorn().getTexture("nut_50_hp"));
		}
		if (hp <= 4 && hp > 0) {
			animation.setTexture(LoadTexture::getBorn().getTexture("nut_low_hp"));
		}
		if (hp <= 0) {
			Message msg;
			msg.type = TypeMsg::DEATH;
			msg.death.creature = this;
			mng->addMessage(msg);
			sf::Vector2f vect = mng->getMap().getFieldIdx({ rect.left, rect.top });
			mng->getMap().setIsPlaced(vect.x, vect.y, false);
		}
	}
}


