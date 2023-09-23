#pragma once
#include<iostream>
#include<cmath>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include "enemies.h"
#include"bohater.h"
#include "charger.h"
#include "game.h"
namespace MyGame {
    class game; // Forward declaration of the game class
}
class charger :  public enemies
{
private:
    float speed = 100;
    float rotationAngle = 0;
    bool isAngry = false;
    sf::Clock canICharge;
public:
    bool callIsDead();
    float hp = 5;
    bool isCharger() const override { return true; }
    sf::Vector2f bohaterPosition;
    void takeDamage(int damage);
    void updateBohaterPosition(sf::Vector2f newPosition);
    void update(float time);
    void move(float time);

    charger(float diff);
};
