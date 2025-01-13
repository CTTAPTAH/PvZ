#include "Zombie.h"

int Zombie::count = 0;

Zombie::Zombie() {}

Zombie::Zombie(int _index_line, TypeObject _type,
	int w_cell, int h_cell) :
	GameObject(_index_line, _type)
{
	rect.width = 50;
	rect.height = 50;
	rect.left = 800 - w_cell / 2 - rect.width/2;
	rect.top = (_index_line * h_cell) + (h_cell / 2) - (rect.height);

	color = { 255,255,255,255 };
	velocity_x = 30;
	current_index = count;
	hp = 3;
	count++;

	//Убрал pos!!!
	//pos.x = 800 - w_cell / 2 - rect.width / 2;
	//pos.y = (_index_line * h_cell) + (h_cell / 2) - (rect.height);
}

Zombie::~Zombie()
{
	std::cout << "Zombie number " << current_index << " is defeat" << std::endl;
}

void Zombie::move(double dt)
{
	rect.left -= velocity_x * dt;
	if (Collision()) {
		velocity_x = 0;
	}
	////std::cout << "Zombie moving, position x: " <<rect.left << "\n";
}

void Zombie::draw(sf::RenderWindow& win)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(rect.width, rect.height));
	rectangle.setPosition(rect.left, rect.top);
	rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	win.draw(rectangle);
}
void Zombie::update(double dt, sf::RenderWindow& win) {
	//Добавил update
	move(dt);
	draw(win);
	std::cout << hp << std::endl;
}
void Zombie::ReceiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::DAMAGE) {
		if (hp != 0) {
			hp-=msg->damage.damage;
		}
		else {
			Message msg;
			msg.type = TypeMsg::DEATH;
			msg.death.creature = this;
			Manager* MGR = Manager::GetBorn();
			MGR->addMessage(msg);
		}
	}
}
bool Zombie::Collision()
{
	return rect.left <= 800 / 9;
}

void Zombie::EatingPlant(double dt)
{
}
