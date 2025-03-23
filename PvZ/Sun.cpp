#include "Sun.h"


sf::Vector2f right_up_angle{800,-200};

float vectorlen(sf::Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void normolize(sf::Vector2f& vector) {
	float len = vectorlen(vector);
	if (len != 0) {
		vector.x /= len;
		vector.y /= len;
	}
}

int Sun::collected_sun = 0;

//sf::Texture* Sun::texture = LoadTexture::getBorn().getTexture("sun");
Sun::Sun(int pos_x, int pos_y, int index_line_)
{
	//texture = Manager::GetBorn()->GetTexture("sun");
	//sprite.setTexture(*texture);
	animation.setTexture(LoadTexture::getBorn().getTexture("sun"));

	rect.left = pos_x;rect.top = pos_y;
	rect.width = 50; rect.height = 50;

	animation.setPosition(rect.left, rect.top);

	idx_line = index_line_;
	start_pos_y = pos_y;

	ground_pos_y = pos_y + 25;

	color = sf::Color::Yellow; color.a = 255;
}

Sun::Sun()
{
	rect.left = 0; rect.top = 0;
	rect.width = 50; rect.height = 50;

	color = sf::Color::Yellow; color.a = 255;
}
Sun::~Sun(){}

void Sun::move(double dt)
{
	const double gravity = 300.0;
	const double v0_y = -150.0;

	if (firstMove) {
		velocity_y = v0_y;
		firstMove = false;
	}

	velocity_y += gravity * dt;

	rect.top += velocity_y * dt;

	/*if (velocity_y < 0 && rect.top <= start_pos_y - 30) {
		velocity_y = 0;
	}*/
	if (rect.top >= ground_pos_y) {
		rect.top = ground_pos_y;
		velocity_y = 0;
	}

	animation.setPosition(float(rect.left), float(rect.top)); // Добавил Н
}

void Sun::draw(sf::RenderWindow& win)
{
	//if (texture) {
	//	sprite.setPosition(rect.left, rect.top);
	//	win.draw(sprite);
	//}
	animation.draw(win); // Добавил Н
}

void Sun::update(double dt, sf::RenderWindow& win)
{
	draw(win);
	if (!touch) {
		move(dt);
	}
	TextureCollisionWithCursor(win, dt);
}

void Sun::receiveMsg(Message* msg)
{
}

void Sun::CollisionWithCursor(sf::RenderWindow& win)
{
	Manager* MGR = Manager::getBorn();

	sf::Vector2i cursor_position = sf::Mouse::getPosition(win);

	sf::Vector2f center_of_circle = sf::Vector2f(rect.left, rect.top) + sf::Vector2f(rect.width / 2.0, rect.height / 2.0);

	double radius = rect.width / 2.0;

    double distance = std::sqrt((cursor_position.x - center_of_circle.x) * (cursor_position.x - center_of_circle.x) + (cursor_position.y - center_of_circle.y) * (cursor_position.y - center_of_circle.y));;

	if (distance <= radius) {

		collected_sun += 1;
		std::cout << collected_sun << std::endl;

		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;
		MGR->addMessage(msg);
	}
}

void Sun::TextureCollisionWithCursor(sf::RenderWindow& win, double dt) {

	Manager* MGR = Manager::getBorn();

	sf::Vector2i cursor_position = sf::Mouse::getPosition(win);

	sf::IntRect cursor_rect{ cursor_position.x, cursor_position.y, 1, 1 };

	if (touch) {

		sf::Vector2f direction = { right_up_angle.x - rect.left, right_up_angle.y - rect.top };

		normolize(direction);

		float speed = 500.0f;
		rect.left += direction.x * dt * (speed*(float)(idx_line+1)/1.8f);
		rect.top += direction.y * dt * (speed*(float)(idx_line+1)/1.8f);
	}

	if (rect.intersects(cursor_rect)) {
		touch = true;
	}

	if (rect.left >= MGR->getWinWidth() || rect.top <= -40) {

		collected_sun += 1;
		std::cout << collected_sun << std::endl;

		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;
		MGR->addMessage(msg);

		touch = false;
	}
}



