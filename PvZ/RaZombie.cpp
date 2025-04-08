#include "RaZombie.h"


std::list<RaZombie*> RaZombie::waiting_list;

RaZombie::RaZombie(int idx_line, int frame_w, int frame_h):
	Zombie(idx_line, frame_w, frame_h)
{
	animation.setTexture(LoadTexture::getBorn().getTexture("razombie"));
	hp = 5;
	velocity_x = 10;
	type = TypeObject::RAZOMBIE;
}

RaZombie::~RaZombie()
{

}

void RaZombie::move(double dt)
{
	if (!victim) {

		if (!isTakeSuns) {
			velocity_x = 30;
			rect.left -= velocity_x * dt;
		}
		else {
			velocity_x = 0;
		}
		animation.setPosition(rect.left, rect.top);
	}
}

void RaZombie::update(double dt, sf::RenderWindow& win)
{
	if (getOnMap() and !onMap) {
		waiting_list.push_back(this);
		onMap = true;
	}
	FindVictimN2(dt);
    MagnetSun(dt);
	move(dt);
	draw(win);
}

void RaZombie::setIsTakeSuns(bool isHappend)
{
	isTakeSuns = isHappend;
	if (!isHappend) {
		animation.setTexture(LoadTexture::getBorn().getTexture("razombie"));
	}
}

void RaZombie::currentSunNullable(RaZombie* owner)
{
	currentSun = nullptr;
	if (std::find(waiting_list.begin(), waiting_list.end(), owner) == waiting_list.end()) {
		waiting_list.push_back(owner);
	}
}

bool RaZombie::getOnMap()
{
	return rect.left + rect.width <= Config::WIN_WIDTH;
}

void RaZombie::MagnetSun(double dt)
{
	
	Manager* MGR = Manager::getBorn();

	auto objlist = MGR->getListObject();

	std::cout << waiting_list.size() << std::endl;

	RaZombie* owner = nullptr;


	if (currentSun && currentSun->GetSunTrapped()) {

		if (currentSun->getIsDead()) {
			setIsTakeSuns(false);
			currentSunNullable(this);
		}
		else {
			animation.setTexture(LoadTexture::getBorn().getTexture("razombie_tr"));
			currentSun->MoveToZombie(dt);
			return;
		}
	}

	if (!waiting_list.empty()) {
		owner = waiting_list.front();
		waiting_list.pop_front();
	}
	else {
		return;
	}

	Sun* sun = nullptr;

	for (auto& elem : objlist) {
		if (elem->getType() == TypeObject::SUN) {
			sun = static_cast<Sun*>(elem);
			if (sun->getOnGround() && !sun->GetSunTrapped()) {
				sun->SetSunTrapped(true);
				sun->SetOwnerSun(owner);
				owner->currentSun = sun;
				owner->isTakeSuns = true;
				return;
			}
		}
	}
	if (std::find(waiting_list.begin(), waiting_list.end(), owner) == waiting_list.end()) {
		waiting_list.push_back(owner);
	}
}




