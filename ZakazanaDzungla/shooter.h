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
#include "wasp.h"
#include "game.h"
namespace MyGame {
    class game; // Forward declaration of the game class
}
class shooter : public enemies
{
private:
    float speed = 0;
    float rotationAngle = 0;
    float timedelay = 1;
    sf::Clock canShoot;
public:
    bool callIsDead(); // For using in game.cpp
    float hp = 5;
    bool isShooter() const override { return true; }
    sf::Vector2f bohaterPosition;
    void takeDamage(int damage);
    void updateBohaterPosition(sf::Vector2f newPosition);
    void update(float time);
    void move(float time);
    void shootin(); // It doesnt work sadly
    shooter(float diff);
};
