#pragma once
#include <SFML/Graphics.hpp>
class Message;

enum class TypeObject {
	UNDEFINED, PEASHOOTER
};
struct Position {
	double x = 0, y = 0;
};

class GameObject
{
protected:
	// �������� ����� ��������
	sf::IntRect rect;
	sf::Color color;
	// ��, ��� ����
	int win_width = 800, win_height = 600; // � config
	Position pos; // �������� �� �����, �.�. ������� rect
	int hp;
	sf::Texture* texture; // �������� �� �����, �.�. ������� rect � color
	int idx_line;
	TypeObject type; // ������ ����� �� �����������. �� ����������� � update
public:
	GameObject();
	GameObject(int idx_line_, TypeObject type);
	GameObject(const GameObject&);
	virtual ~GameObject();

	void ReceiveDamage();
	virtual void update(double dt, sf::RenderWindow& win);
	void UpdatePosition(double dt, double speed); // ������������� �� move � ������ ����� ������
	void Animation(double dt);
	//void isLive();
	void Collision();

	//static int GetId();
	Position getPosition();
	virtual void draw(sf::RenderWindow& win);
	virtual void setPosition(Position pos_);
	virtual void SendMsg(double dt);
	virtual void ReceiveMsg(Message* msg);
};