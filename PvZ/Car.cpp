#include "Car.h"
#define INFINITY INT_MAX

//sf::Texture* Car::texture = Manager::GetBorn()->GetTexture("car");

Car::Car(int index_line_, TypeObject type, int w_cell, int h_cell)
	: GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("car"),
			Config::CAR_FRAME_WIDTH,
			Config::CAR_FRAME_HEIGHT,
			Config::CAR_FRAME_COUNT,
			Config::CAR_FRAME_TIME,
			{200,(index_line_ * h_cell + rect.height / 2.0f)+90 }
	    ),
		{ 200, (index_line_ * h_cell + rect.height / 2.0f)+90, Config::CAR_FRAME_WIDTH, Config::CAR_FRAME_HEIGHT},
		INFINITY,
		index_line_,
		type,
		TypeEntity::CAR
		)
{
}
Car::Car(){}
Car::~Car() { /*std::cout << "Car was deleted" << std::endl;*/ }

void Car::update(double dt, sf::RenderWindow& win)
{
	draw(win);
	if (touch) {
		move(dt);
		checkboarders();
	}
	CollisionWithZombie(dt);
}

void Car::receiveMsg(Message* msg)
{
}

void Car::draw(sf::RenderWindow& win)
{
	animation.draw(win);
}

void Car::move(double dt)
{
	rect.left += dt * velocity_x;
	animation.setPosition(rect.left, rect.top); // Н добавил
}

void Car::CollisionWithZombie(double dt)
{
	Manager* MGR = Manager::getBorn();
	auto object_list = MGR->getListObject();

	for (auto elem : object_list) {
		if (elem->getTypeObj() == TypeObject::ZOMBIE and rect.intersects(elem->getRect())) {
			if (this->idx_line == elem->getIdxLine()) {
				SoundEditor::getBorn()->playSound("cars_start", 20);
				touch = true;
				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = elem;
				MGR->addMessage(msg);
			}
		}
	}
}

void Car::checkboarders()
{
	Manager* MGR = Manager::getBorn();

	if (rect.left >= MGR->getWinWidth()) {
		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;
		MGR->addMessage(msg);
	}
}

