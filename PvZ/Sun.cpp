#include "Sun.h"
#include "RaZombie.h"

int Sun::collected_sun = 0;

sf::Vector2f right_up_angle{ 150,-40 };

float vectorlen(sf::Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void normolize(sf::Vector2f& vector) {
	float len = vectorlen(vector);
	if (len != 0) {
		vector.x /= len;
		vector.y /= len;
	}
	else {
		vector = {0.f, 0.f};
	}
}
Sun::Sun(float pos_x, float pos_y, int index_line_) :
	GameObject(
		Animation(
			LoadTexture::getBorn().getTexture("sun"),
			Config::SUN_FRAME_WIDTH,
			Config::SUN_FRAME_HEIGHT,
			Config::SUN_FRAME_COUNT,
			Config::SUN_FRAME_TIME,
			{ pos_x,pos_y }
		),
		{ pos_x,pos_y,Config::SUN_FRAME_WIDTH, Config::SUN_FRAME_HEIGHT },
		hp = 0,
		idx_line = index_line_,
		TypeObject::UNDEFINED,
		TypeEntity::SUN
	)
{
	start_pos_y = pos_y;
	ground_pos_y = pos_y + 25;
}

Sun::Sun()
{
	rect.left = 0; rect.top = 0;
	rect.width = 50; rect.height = 50;
}
Sun::~Sun() {}

void Sun::move_from_sunflower(double dt)
{
	current_motion = MOVE_SUN;
	const double gravity = 300.0;
	const double v0_y = -150.0;

	if (firstMove) {
		velocity_y = v0_y;
		firstMove = false;
	}

	velocity_y += gravity * dt;

	rect.top += velocity_y * dt;

	if (rect.top >= ground_pos_y) {
		rect.top = ground_pos_y;
		velocity_y = 0;
		current_motion = IDLE_SUN;
		onGround = true;
	}
}

void Sun::draw(sf::RenderWindow& win)
{
	if (current_motion == MOVE_SUN || SunTrappedByZombie) {
		animation.setPosition(float(rect.left), float(rect.top));
	}
	animation.draw(win);
}

void Sun::update(double dt, sf::RenderWindow& win)
{
	draw(win);
	if (!touch && !SunTrappedByZombie) {
		move_from_sunflower(dt);
	}
	if (SunTrappedByZombie) {
		checkTimer();
	}
	TextureCollisionWithCursor(win, dt);
}

void Sun::receiveMsg(Message* msg){}

void Sun::TextureCollisionWithCursor(sf::RenderWindow& win, double dt) {

	Manager* MGR = Manager::getBorn();

	sf::Vector2f cursor_position = (sf::Vector2f)sf::Mouse::getPosition(win);

	sf::FloatRect cursor_rect{ cursor_position.x, cursor_position.y, 1, 1 };

	if (touch) {

		if (!sound_played) {
			SoundEditor::getBorn()->playSound("sun_pull_up", 15);
			sound_played = true;
		}

		sf::Vector2f direction = { right_up_angle.x - rect.left, right_up_angle.y - rect.top };

		normolize(direction);


		float speed = 500.0f;
		rect.left += direction.x * dt * (speed * (float)(idx_line + 1) / 2.3f);
		rect.top += direction.y * dt * (speed * (float)(idx_line + 1) / 2.3f);
	}

	if (rect.intersects(cursor_rect)) {
		if (!touch) { // добавил Н
			Player& player = Manager::getBorn()->getPlayer(); // добавил Н
			player.setMoney(player.getMoney() + Config::SUN_PRICE); // добавил Н
		}
		touch = true;
		current_motion = MOVE_SUN;
	}

	// Исправи if Н. Было: rect.left >= MGR->getWinWidth() || rect.top <= 4
	if (rect.left >= MGR->getWinWidth() || rect.top < 4) {

		collected_sun += 1;
		//std::cout << collected_sun << std::endl;

		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;
		MGR->addMessage(msg);
		isdead = true;
		touch = false;
		current_motion = IDLE_SUN;
	}
}

void Sun::SetSunTrapped(bool isHappend)
{
	SunTrappedByZombie = isHappend;
}

bool Sun::GetSunTrapped()
{
	return SunTrappedByZombie;
}

void Sun::SetOwnerSun(RaZombie* owner) {
	owner_zombie = owner;
}
void Sun::MoveToZombie(double dt)
{
	if (!owner_zombie) return;

	if (!touch) {

		zombie_timer += dt;

		sf::Vector2f position = {
			(float)owner_zombie->getRect().left,
			(float)owner_zombie->getRect().top
		};

		sf::Vector2f direction = { position.x - rect.left, position.y - rect.top };

		normolize(direction);

		rect.left += direction.x * dt * variable_speed;
		rect.top += direction.y * dt * variable_speed;

		if (rect.intersects(owner_zombie->getRect())) {

			SunTrappedByZombie = false;
			owner_zombie->setIsTakeSuns(false);
			owner_zombie->currentSunNullable(owner_zombie);
			owner_zombie = nullptr;

			Message msg;
			msg.type = TypeMsg::DEATH;
			msg.death.creature = this;
			Manager::getBorn()->addMessage(msg);

			isdead = true;
		}
	}
	else {
		SunTrappedByZombie = false;
		owner_zombie->setIsTakeSuns(false);
		owner_zombie->currentSunNullable(owner_zombie);
		owner_zombie = nullptr;
	}
}


void Sun::checkTimer()
{
	if (zombie_timer < 0.5) {
		variable_speed = 100;
	}
	if (zombie_timer >= 0.5 && zombie_timer<1) {
		variable_speed = 200;
	}
	else if (zombie_timer >= 1 && zombie_timer < 2) {
		variable_speed = 400;
	}
	else if (zombie_timer >= 2) {
		variable_speed = 600;
	}
}

bool Sun::getOnGround()
{
	return onGround;
}
bool Sun::isTouched() const {
	return touch;
}


