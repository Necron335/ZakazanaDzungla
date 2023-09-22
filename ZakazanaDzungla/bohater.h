#pragma once

#include<iostream>
#include<cmath>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include "entities.h"
#include<memory>
namespace MyGame {
    class game; // Forward declaration of the game class

    class bohater : public entities {
    private:
        double pi = 3.1415;
        sf::RenderWindow& window;
        float speed = 500;
        
        bool canRotate = true;

    public:
        bool isDead = false;
        float hp = 20;
        float CalculateRotationAngle();
        void changeWeapon(int weapon);
        void deductHP(float amount);

        void update(float time);

        void move(float time);

        bohater(sf::RenderWindow& win);

        sf::Vector2f returnHeroPosition(bohater* bohaterakt);
    };
}