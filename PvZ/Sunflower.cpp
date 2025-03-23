#include "Sunflower.h"

Sunflower::Sunflower(int index_line_, TypeObject type_, int pos_x, int pos_y)
	:GameObject(Animation(),
		{pos_x, pos_y, 100, 100},
		3,
		index_line_,
		type_
	)
{
	rect.left = pos_x; rect.top = pos_y+25;
	rect.height = 50; rect.width = 50;

	color.r = 0; color.g = 255; color.b = 0; color.a = 255;

	hp = 3;

	time_to_reaper_sun = 10;
	//time_to_reaper_sun = 10;
	time_to_reaper_sun = 5;
	animation.setTexture(LoadTexture::getBorn().getTexture("sunflower"));// Добавил Н
	animation.setPosition(float(pos_x), float(pos_y)); // Добавил Н
}
Sunflower::Sunflower()
{
	rect.left = 0; rect.top = 0; rect.height = 50; rect.width = 50;
	color.r = 0; color.g = 255; color.b = 0; color.a = 255;
	hp = 3;
	time_to_reaper_sun = 10;
	idx_line = -1;
	type = TypeObject::PLANT;
	animation.setTexture(LoadTexture::getBorn().getTexture("sunflower")); // Добавил Н
}
Sunflower::~Sunflower(){}

void Sunflower::dropsun(double dt)
{
	Manager* MGR = Manager::getBorn();

	current_time += dt;

	if (current_time >= time_to_reaper_sun) {
		current_time = 0;

		Sun* sun = new Sun(random(rect.left+rect.width/4.0, rect.left+rect.width/2.0), rect.top + rect.height / 4.0, this->getIdxLine());

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
			Message MSG;
			MSG.type = TypeMsg::DEATH;
			MSG.death.creature = this;
			MGR->addMessage(MSG);
		}
	}
}

void Sunflower::update(double dt, sf::RenderWindow& win)
{
	dropsun(dt);
	animation.update(dt);
	draw(win);
}

void Sunflower::setRect(sf::IntRect rect_)
{
	rect = rect_;
	animation.setPosition(rect.left, rect.top);
}

int Sunflower::random(int a, int b)
{
    return rand() % (b - a + 1) + a;
}
