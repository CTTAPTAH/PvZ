#include "Zombie.h"
#define DEFAULT_ZOMBIE_SPEED 100
#define IDLE_ZOMBIE_SPEED 0

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
	velocity_x = 100;
	current_index = count;
	hp = 2;
	count++;

	// увеличиваем количество зомби на указанной линии
	Manager* mng = Manager::GetBorn();
	mng->addZombieOnLine(_index_line);

	// добавил
	victim = nullptr;
	//”брал pos!!!
	//pos.x = 800 - w_cell / 2 - rect.width / 2;
	//pos.y = (_index_line * h_cell) + (h_cell / 2) - (rect.height);
}

Zombie::~Zombie()
{
	std::cout << "Zombie number " << current_index << " is defeat" << std::endl;

	// уменьшаем количество зомби на указанной линии
	Manager* mng = Manager::GetBorn();
	mng->removeZombieOnLine(idx_line);
}

void Zombie::move(double dt)
{
	if (!victim) { // добавил условие
		rect.left -= velocity_x * dt;
	}
	
	//std::cout << "Zombie moving, position x: " <<dt << "\n";
	//std::cout << dt << " " << velocity_x << " " << velocity_x * dt << std::endl;
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
	//ƒобавил update
	FindVictimN2(dt);
	// либо то, что ниже, либо выше
	//if (!victim)
	//	FindVictimN();
	//if (victim)

	//EatingPlantsN(dt);
	move(dt);
	draw(win);
	//CollisionWithPlants(dt);
	//std::cout << hp << std::endl;
}
void Zombie::ReceiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::DAMAGE and
		this == msg->damage.who_receive) {
		if (hp > 0) {
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
bool Zombie::Collision1()
{
	return rect.left <= 800 / 9;
}
void Zombie::EatingPlants(double dt, GameObject* current_object)
{
	Manager* MGR = Manager::GetBorn();

	if (!isEating) {
		isEating = true;
	}
	if (isEating) {

		int cur_plant_hp = current_object->getHp();

		if (cur_plant_hp <= 0) {
			velocity_x = DEFAULT_ZOMBIE_SPEED;
			isEating = false;
			return;
		}

		reload -= dt;

		velocity_x = IDLE_ZOMBIE_SPEED;

		if (reload <= 0) {
			reload = time_reload;
			Message msg;
			msg.type = TypeMsg::DAMAGE;
			msg.damage.damage = damage;
			msg.damage.who_receive = current_object;
			MGR->addMessage(msg);
		}
	}

}
void Zombie::CollisionWithPlants(double dt)
{
	Manager* MGR = Manager::GetBorn();

	std::list<GameObject*> objects = MGR->getListObject();

	for (auto obj : objects) {
		if (obj->getType() == TypeObject::PLANT) {
			if (Collision1() && idx_line == obj->getIdxLine()) {
				//std::cout << "Yes" << std::endl;
				EatingPlants(dt, obj);
				break;
			}
		}
	}
}

// добавил
void Zombie::FindVictimN()
{
	Manager* mng = Manager::GetBorn();
	std::list<GameObject*> objects = mng->getListObject();
	for (auto obj : objects) {
		if (obj->getType() == TypeObject::PLANT) {
			if (Collision1() and idx_line == obj->getIdxLine()) {
				victim = obj;
			}
		}
	}
}
void Zombie::EatingPlantsN(double dt)
{
	if (victim) {
		reload -= dt;
		if (reload <= 0) {
			reload = time_reload;

			Message msg;
			msg.type = TypeMsg::DAMAGE;
			msg.damage.damage = damage;
			msg.damage.who_receive = victim;

			Manager* mng = Manager::GetBorn();
			mng->addMessage(msg);

			if (victim->getHp() - damage <= 0) {
				victim = nullptr;
				reload = time_reload;
			}
		}
	}
}
void Zombie::FindVictimN2(double dt)
{
	Manager* mng = Manager::GetBorn();
	std::list<GameObject*> objects = mng->getListObject();
	victim = nullptr;
	for (auto obj : objects) {
		if (obj->getType() == TypeObject::PLANT) {
			if (Collision1() and idx_line == obj->getIdxLine()) {
				victim = obj;
				isEating = true;
				break;
			}
		}
	}

	if (victim) {
		reload -= dt;
		if (reload <= 0) {
			reload = time_reload;

			Message msg;
			msg.type = TypeMsg::DAMAGE;
			msg.damage.damage = damage;
			msg.damage.who_receive = victim;

			Manager* mng = Manager::GetBorn();
			mng->addMessage(msg);
		}
	}
	else {
		if (isEating) {
			isEating = false;
			reload = time_reload;
		}
	}
}
