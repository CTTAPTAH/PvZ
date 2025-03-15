#include "Sun.h"

int Sun::collected_sun = 0;

sf::Texture* Sun::texture = Manager::GetBorn()->GetTexture("sun");

Sun::Sun(int pos_x, int pos_y)
{
	//texture = Manager::GetBorn()->GetTexture("sun");
	sprite.setTexture(*texture);
	rect.left = pos_x;rect.top = pos_y;
	rect.width = 50; rect.height = 50;

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

}

void Sun::draw(sf::RenderWindow& win)
{
	if (texture) {
		sprite.setPosition(rect.left, rect.top);
		win.draw(sprite);
	}
}

void Sun::update(double dt, sf::RenderWindow& win)
{
	draw(win);
	move(dt);
	TextureCollisionWithCursor(win);
}

void Sun::ReceiveMsg(Message* msg)
{
	
}

void Sun::CollisionWithCursor(sf::RenderWindow& win)
{
	Manager* MGR = Manager::GetBorn();

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

void Sun::TextureCollisionWithCursor(sf::RenderWindow& win) {

	Manager* MGR = Manager::GetBorn();

	sf::Vector2i cursor_position = sf::Mouse::getPosition(win);

	sf::IntRect cursor_rect{ cursor_position.x, cursor_position.y, 1, 1 };

	if (rect.intersects(cursor_rect)) {

		collected_sun += 1;
		std::cout << collected_sun << std::endl;

		Message msg;
		msg.type = TypeMsg::DEATH;
		msg.death.creature = this;
		MGR->addMessage(msg);
	}
}



