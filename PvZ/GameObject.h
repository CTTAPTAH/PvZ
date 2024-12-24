#pragma once

class Message;

struct Position {
	double x, y;
};

class GameObject
{
private:
	Position pos;
	int hp;
	// Texture*
	int idx_line;
	int id;
public:
	GameObject();
	GameObject(const GameObject&);
	virtual ~GameObject();

	void ReceiveDamage();
	void UpdatePosition();
	void Animation();
	void isLive();
	void Collision();

	//static int GetId();
	Position GetPosition();
	virtual void SendMsg(double dt);
	virtual void ReceiveMsg(Message msg);
};