#pragma once
#include "SFML/Graphics.hpp"
#include"GameObject.h"
#include "Manager.h"
#include "Chomper.h"
#include <iostream>
#include "Map.h"

//static int set_counter = 0;

struct GameOverInfo {

    int set_counter;
    bool gameOver;
    double alpha_channel;
    sf::Color color;
    sf::RectangleShape generalrect;

    sf::Sprite sprite;
    sf::Texture* texture;

    static GameOverInfo& getBorn() {
        static GameOverInfo instance;
        return instance;
    }

private:
    GameOverInfo() :gameOver(false), alpha_channel(0), color({ 0,0,0, sf::Uint8(alpha_channel)}), generalrect({Config::WIN_WIDTH, Config::WIN_HEIGHT}) {
        generalrect.setPosition({ 0, 0 });    
        texture = LoadTexture::getBorn().getTexture("end_screen");
        sprite.setTexture(*texture);
        sprite.setPosition({ Config::WIN_WIDTH / 2.0- Config::WIN_WIDTH/5.0, Config::WIN_HEIGHT/5.0 });
    }
public:
    GameOverInfo(const GameOverInfo&) = delete;
    GameOverInfo& operator=(const GameOverInfo&) = delete;
    ~GameOverInfo() {}

    void GameOver(double dt, sf::RenderWindow& win) {
        if (gameOver) {
            if (alpha_channel <= 255) {
                alpha_channel += dt * 200;
                if (alpha_channel > 255) alpha_channel = 255;
                
            }
            color.a = static_cast<sf::Uint8>(alpha_channel); 
            color = { 0, 0, 0, color.a };
            generalrect.setFillColor(color);
           
            win.draw(generalrect);

            if (color.a >= 255) {
                win.draw(sprite);
            }
        }
    }
    void setGameOver(bool isHappend) {
        if (set_counter < 1) {
            gameOver = isHappend;
            SoundEditor::getBorn()->playSound("Noo", 50);
            set_counter++;
        }
        return;
    }
    bool getGameOver() {
        return gameOver;
    }
    double getAlpha() {
        return alpha_channel;
    }
};

class Zombie : public GameObject
{
protected:
    double velocity_x;

    static int count;
    int current_index;
    int damage;
    bool isEating = false;

    bool haveFrozenEffect = false;
    double frozen_timer = 0;
    bool wasFrozenSpeedSet = false;

    const double time_reload = 1;
    double reload = 0;

    GameObject* victim;
    sf::Sound chewingSound;

    bool hasEnteredScreen = false; // добавил Н
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
    virtual void tryRegisterOnLine();
    void receiveMsg(Message* msg) override;

    // добавил при создании анмации
    void FindVictimN(); // почему-то без ошибок
    void EatingPlantsN(double dt); // почему-то без ошибок
    void FindVictimN2(double dt); // менее производительно, но без потенциальных ошибок

    void ZombieIsFrosen(double dt);

    void setZombieFrozenNull();

    void setHaveFrozenEffect(bool isHappend);
    void isGameOver();
    // геттеры, сеттеры
    int getSpeed() const;
    void setVictim();

};