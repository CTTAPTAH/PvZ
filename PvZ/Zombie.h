#pragma once
#include "SFML/Graphics.hpp"
#include"GameObject.h"
#include "Manager.h"
#include <iostream>
#include "Map.h"


class Zombie : public GameObject
{
protected:

    double velocity_x;
    static int count;
    int current_index;
    int damage;
    bool isEating = false;

    const double time_reload = 1;
    double reload = 0;

    GameObject* victim;

public:
    Zombie();
    Zombie(int _index_line, int frame_w, int frame_h);
    ~Zombie();

    //Процессы
    bool Collision1();

    //Механики
    void EatingPlants(double dt, GameObject* current_object);
    void CollisionWithPlants(double dt);
    virtual void move(double dt);
    virtual void draw(sf::RenderWindow& win);
    void update(double dt, sf::RenderWindow& win) override;
    void receiveMsg(Message* msg) override;

    // добавил при создании анмации
    void FindVictimN(); // почему-то без ошибок
    void EatingPlantsN(double dt); // почему-то без ошибок
    void FindVictimN2(double dt); // менее производительно, но без потенциальных ошибок
};