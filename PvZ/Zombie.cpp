#include "Zombie.h"

#define IDLE_ZOMBIE_SPEED 0



int Zombie::count = 0;

//bool Zombie::gameOver = false;
//
//double Zombie::alpha_channel = 0;

Zombie::Zombie() {}

Zombie::Zombie(int _index_line, int frame_w, int frame_h) :
	GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("zombie"),
			frame_w,
			frame_h,
			Config::ZOMBIE_FRAME_COUNT,
			Config::ZOMBIE_FRAME_TIME,
			{ Config::WIN_WIDTH + Config::W_CELL * 2, (_index_line * Config::H_CELL) + (Config::H_CELL / 2) - (rect.height) }
		),
		{ Config::WIN_WIDTH + Config::W_CELL * 2, (_index_line * Config::H_CELL) + (Config::H_CELL / 2) - (rect.height), Config::ZOMBIE_FRAME_WIDTH, Config::ZOMBIE_FRAME_HEIGHT },
		Config::DEFAULT_ZOMBIE_HP,
		_index_line,
		TypeObject::ZOMBIE,
		TypeEntity::ZOMBIE
	),
	velocity_x(Config::DEFAULT_ZOMBIE_SPEED),
	damage(Config::DEFAULT_ZOMBIE_DAMAGE),
	reload(Config::DEFAULT_ZOMBIE_RELOAD),
	time_reload(Config::DEFAULT_ZOMBIE_TIME_RELOAD),
	victim(nullptr),
	current_index(count + 1),
	hasEnteredScreen(false)
{
	//std::cout << "Zombie number " << current_index << " cr" << std::endl;
	//velocity_x = 0; //проверял точность арбуза Н.
	//rect.left -= rand() % (1000 - 300 + 1) + 300; //проверял точность арбуза Н.

	//setRect(rect);
	chewingSound.setBuffer(SoundEditor::getBorn()->getBuffer("zombie_chewing"));
	chewingSound.setLoop(true);
	chewingSound.setVolume(10);
	//Manager::getBorn()->addZombieOnLine(_index_line);
	count++;
}

Zombie::~Zombie()
{
	//std::cout << "Zombie number " << current_index << " is defeat" << std::endl;

	// уменьшаем количество зомби на указанной линии
	Manager* mng = Manager::getBorn();
	mng->removeZombieOnLine(idx_line);
}

void Zombie::move(double dt)
{
	if (!victim) { // добавил условие
		rect.left -= velocity_x * dt;
		animation.setPosition(rect.left, rect.top);
	}
	//std::cout << velocity_x << std::endl;

	//std::cout << "Zombie moving, position x: " <<dt << "\n";
	//std::cout << dt << " " << velocity_x << " " << velocity_x * dt << std::endl;
}

void Zombie::draw(sf::RenderWindow& win)
{
	animation.draw(win);
}
void Zombie::update(double dt, sf::RenderWindow& win) {
    
	if (!getIsDead()) {
		FindVictimN2(dt);
		move(dt);
		tryRegisterOnLine(); // Добавил Н
		draw(win);
		ZombieIsFrosen(dt);
		isGameOver();
	}
}
void Zombie::tryRegisterOnLine()
{
	Manager* mng = Manager::getBorn();
	if (!hasEnteredScreen and rect.left < mng->getWinWidth()) {
		mng->addZombieOnLine(idx_line);
		hasEnteredScreen = true;
	}
}
void Zombie::receiveMsg(Message* msg)
{
	if (msg->type == TypeMsg::DEATH && msg->death.creature->getTypeObj() == TypeObject::PLANT) {
		if (victim == msg->death.creature) {
			victim = nullptr;
		}
	}
	if (msg->type == TypeMsg::DAMAGE and
		this == msg->damage.who_receive) {
		if (hp > 0) {
			hp -= msg->damage.damage;
			if (hp <= 0) {
				Message msg;
				msg.type = TypeMsg::DEATH;
				msg.death.creature = this;
				Manager* MGR = Manager::getBorn();
				MGR->addMessage(msg);
				isdead = true; // <--- это важно!
			}
		}
	}
}
void Zombie::EatingPlants(double dt, GameObject* current_object)
{
	Manager* MGR = Manager::getBorn();

	if (!isEating) {
		isEating = true;
	}
	if (isEating) {

		int cur_plant_hp = current_object->getHp();

		if (cur_plant_hp <= 0) {
			velocity_x = Config::DEFAULT_ZOMBIE_SPEED;
			isEating = false;
			return;
		}

		reload -= dt;

		velocity_x = Config::DEFAULT_ZOMBIE_IDLE_SPEED;

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
void Zombie::FindVictimN2(double dt)
{
	Manager* mng = Manager::getBorn();
	std::list<GameObject*> objects = mng->getListObject();
	victim = nullptr;
	for (auto obj : objects) {
		if (obj->getTypeObj() == TypeObject::PLANT and !obj->getIsDead()) {

			if (obj->getTypeEnt() == TypeEntity::CHOMPER) {
				Chomper* chomp = dynamic_cast<Chomper*>(obj);
				if (chomp and !chomp->getIsEating()) {
					break;
				}
			}

			if (rect.intersects(obj->getRect()) and idx_line == obj->getIdxLine()) {
				victim = obj;
				isEating = true;
				break;
			}
		}
	}


	if (victim) {

		if (chewingSound.getStatus() != sf::Sound::Playing) {
			chewingSound.play();
		}
		reload -= dt;
		if (reload <= 0) {
			reload = time_reload;

			Message msg;
			msg.type = TypeMsg::DAMAGE;
			msg.damage.damage = damage;
			msg.damage.who_receive = victim;

			Manager* mng = Manager::getBorn();
			mng->addMessage(msg);
		}
	}
	else {
		if (isEating) {
			isEating = false;
			reload = time_reload;
		}
		if (chewingSound.getStatus() == sf::Sound::Playing) {
			chewingSound.stop();
		}
	}
}

// геттеры, сеттеры
int Zombie::getSpeed() const
{
	if (victim) {
		return 0;
	}
	else {
		return velocity_x;
	}
}

void Zombie::setHaveFrozenEffect(bool isHappend)
{
	haveFrozenEffect = isHappend;
}

void Zombie::ZombieIsFrosen(double dt)
{
	if (haveFrozenEffect) {

		if (!wasFrozenSpeedSet) {
			velocity_x = Config::DEFAULT_ZOMBIE_SPEED/ 2.0f;
			wasFrozenSpeedSet = true;
		}
		frozen_timer += dt;
	}
	if (frozen_timer >= 2) {
		haveFrozenEffect = false;
		velocity_x = Config::DEFAULT_ZOMBIE_SPEED;
		frozen_timer = 0;
		wasFrozenSpeedSet = false;
	}
}

void Zombie::setVictim()
{
	victim = nullptr;
}

void Zombie::setZombieFrozenNull()
{
	frozen_timer = 0;
}

void Zombie::isGameOver() {
	if (rect.left + rect.width <= 0) {
		GameOverInfo::getBorn().setGameOver(true);
	}
}
