#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "SoundEditor.h"

class Message;

enum class TypeObject {
	UNDEFINED, PLANT, ZOMBIE, PROJECTILE
};
enum class TypeEntity {
	UNDEFINED,

	// растения
	PEASHOOTER,
	SNOWPEASHOOTER,
	SUNFLOWER,
	WALLNUT,
	MELLONPULT,
	CHOMPER,

	// зомби
	ZOMBIE,
	NEWSPAPER_ZOMBIE,
	RAZOMBIE,
	CONUS_ZOMBIE,
	DISCO_ZOMBIE,

	// пульки
	PEA_PROJECTILE,
	SNOW_PEA_PROJECTILE,

	MELON_PROJECTILE,

	// другое
	CAR,
	SUN
};

class GameObject
{
protected:
	Animation animation;
	bool sound_played;
	sf::FloatRect rect;
	int hp;
	bool isdead = false;
	int idx_line;
	TypeObject type_obj;
	TypeEntity type_ent;
public:
	// конструкторы, деструкторы
	GameObject();
	GameObject(Animation animation_, sf::FloatRect rect_,
		int hp_, int idx_line_,
		TypeObject type_obj_, TypeEntity type_ent_);
	GameObject(const GameObject&) = default;
	virtual ~GameObject() = default;

	// методы
	// чисто виртуальные методы
	virtual void receiveMsg(Message* msg) = 0;
	virtual void update(double dt, sf::RenderWindow& win) = 0;
	virtual void draw(sf::RenderWindow& win) = 0;

	// геттеры, сеттеры
	Animation getAnimetion() const;
	sf::FloatRect getRect() const;
	int getHp() const;
	int getIdxLine() const;
	bool getIsDead() const;
	TypeObject getTypeObj() const;
	TypeEntity getTypeEnt() const;
	void setRect(sf::FloatRect rect_);
	void setDead(bool isHappend);
};