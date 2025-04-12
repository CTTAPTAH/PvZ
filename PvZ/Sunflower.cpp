#include "Sunflower.h"

Sunflower::Sunflower(sf::Vector2f pos, int index_line_)
	:GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("sunflower"),
			Config::SUNFLOWER_FRAME_WIDTH,
			Config::SUNFLOWER_FRAME_HEIGHT,
			Config::SUNFLOWER_FRAME_COUNT,
			Config::SUNFLOWER_FRAME_TIME,
			pos
		),
		{ pos.x, pos.y, Config::SUNFLOWER_FRAME_WIDTH, Config::SUNFLOWER_FRAME_HEIGHT },
		Config::SUNFLOWER_HP,
		index_line_,
		TypeObject::PLANT,
		TypeEntity::SUNFLOWER
	),
	time_to_reaper_sun(Config::TIME_TO_REAPEAR_SUN)
{ // Добавил Н
}
Sunflower::Sunflower()
{
	//rect.left = 0; rect.top = 0; rect.height = 50; rect.width = 50;
	////color.r = 0; color.g = 255; color.b = 0; color.a = 255;
	//hp = 3;
	//time_to_reaper_sun = 10;
	//idx_line = -1;
	//type = TypeObject::PLANT;
	//animation.setTexture(LoadTexture::getBorn().getTexture("sunflower")); // Добавил Н
}
Sunflower::~Sunflower() {}

int random(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void Sunflower::dropsun(double dt)
{
	Manager* MGR = Manager::getBorn();

	current_time += dt;

	if (current_time >= time_to_reaper_sun) {
		current_time = 0;

		Sun* sun = new Sun(random(rect.left + rect.width / 4.0, rect.left + rect.width / 2.0), rect.top + rect.height / 4.0, this->getIdxLine());

		Message msg;
		msg.type = TypeMsg::CREATE;
		msg.create.new_object = sun;
		MGR->addMessage(msg);
	}

}

void Sunflower::draw(sf::RenderWindow& win)
{
	//sf::RectangleShape rectangle;
	//rectangle.setSize(sf::Vector2f(rect.width, rect.height));
	//rectangle.setPosition(rect.left, rect.top);
	//rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	//win.draw(rectangle);
	animation.draw(win);
}

void Sunflower::receiveMsg(Message* msg)
{
	Manager* MGR = Manager::getBorn();

	if (msg->type == TypeMsg::DAMAGE && this == msg->damage.who_receive) {
		hp -= msg->damage.damage;
		if (hp <= 0) {
			isdead = true;
			Message MSG;
			MSG.type = TypeMsg::DEATH;
			MSG.death.creature = this;
			MGR->addMessage(MSG);
			sf::Vector2f vect = MGR->getMap().getFieldIdx({ rect.left, rect.top });
			MGR->getMap().setIsPlaced(vect.x, vect.y, false);
		}
	}
}

void Sunflower::update(double dt, sf::RenderWindow& win)
{
	if (!isdead) {
		dropsun(dt);
		animation.update(dt);
		draw(win);
	}
}

void Sunflower::setRect(sf::FloatRect rect_)
{
	rect = rect_;
	animation.setPosition(rect.left, rect.top);
}


