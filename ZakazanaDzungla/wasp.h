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
    float pi = 3.1415;
    float speed = 200;
    float rotationAngle = 0;
    float hp = 5;
    sf::Texture teksturabazowa;

    float CalculateRotationAngle(const sf::Vector2f& source, const sf::Vector2f& target);

public:
    bool isWasp() const override { return true; }
    sf::Vector2f bohaterPosition;

    void updateBohaterPosition(sf::Vector2f newPosition);
    void update(float time);
    void move(float time);

    wasp();
};
