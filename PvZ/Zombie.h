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

    //��������
    bool Collision1();

    //��������
    void EatingPlants(double dt, GameObject* current_object);
    void CollisionWithPlants(double dt);
    virtual void move(double dt);
    virtual void draw(sf::RenderWindow& win);
    void update(double dt, sf::RenderWindow& win) override;
    void receiveMsg(Message* msg) override;

    // ������� ��� �������� �������
    void FindVictimN(); // ������-�� ��� ������
    void EatingPlantsN(double dt); // ������-�� ��� ������
    void FindVictimN2(double dt); // ����� ���������������, �� ��� ������������� ������
};