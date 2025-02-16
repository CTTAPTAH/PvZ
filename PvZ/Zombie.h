#pragma once
#include "SFML/Graphics.hpp"
#include"GameObject.h"
#include "Manager.h"
#include <iostream>
#include "Map.h"

class Zombie : public GameObject
{
private:
    double velocity_x;
    static int count;
    int current_index;
    int damage = 1;
    int time_to_eat_plant;
    bool isEating = false;

    const double time_reload = 1;
    double reload = 0;
   
public:
    Zombie();
    Zombie(int _index_line, TypeObject _type, int w_cell, int h_cell);
    ~Zombie();

    //Процессы
    bool Collision1();

    //Механики
    void EatingPlants(double dt, GameObject* current_object);
    void CollisionWithPlants(double dt);
    void move(double dt);
    void draw(sf::RenderWindow& win);
    void update(double dt, sf::RenderWindow& win) override;
    void ReceiveMsg(Message* msg) override;
};