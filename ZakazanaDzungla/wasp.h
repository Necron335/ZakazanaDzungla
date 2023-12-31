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
class wasp : public enemies
{
private:
    float speed = 200;
    float rotationAngle = 0;
public:
    bool callIsDead();
    float hp = 5;
    bool isWasp() const override { return true; }
    sf::Vector2f bohaterPosition;
    void takeDamage(int damage);
    void updateBohaterPosition(sf::Vector2f newPosition);
    void update(float time);
    void move(float time);

    wasp(float diff);
};
