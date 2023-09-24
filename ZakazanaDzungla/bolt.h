#pragma once
#include "projectiles.h"
#include "enemies.h"
#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <SFML/Graphics.hpp>
class bolt : public projectiles
{
private:
    sf::Vector2f pos;

public:
    bool isBolt() const override { return true; }
    void move(float time);
    void update(float time);
    bolt();
    void handleCollisionWithEnemy();

    ;
};

