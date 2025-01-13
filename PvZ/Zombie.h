#pragma once
#include "SFML/Graphics.hpp"
#include"GameObject.h"
#include "Manager.h"
#include <iostream>

class Zombie : public GameObject
{
private:
    float velocity_x;
    static int count;
    int current_index;
    int damage = 1;
public:
    Zombie();
    Zombie(int _index_line, TypeObject _type, int w_cell, int h_cell);
    ~Zombie();

    //Процессы
    bool Collision();

    //Механики
    void EatingPlant(double dt);
    void move(double dt);
    void draw(sf::RenderWindow& win);
    void update(double dt, sf::RenderWindow& win) override;
    void ReceiveMsg(Message* msg) override;
};


