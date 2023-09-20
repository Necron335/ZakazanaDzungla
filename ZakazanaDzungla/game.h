#pragma once
#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "entities.h"
#include "bohater.h"
#include "game.h"
#include "wasp.h"
#include "background.h"
class bohater;
namespace MyGame {
    class game {
    private:
        sf::RenderWindow window;
        double pi = 3.1415;
        float bohaterspeed = 500;
        float bohaterhp = 100;

    public:
        background back;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bohater* findBohater();
        std::vector<std::unique_ptr<entities>> vectorofentities;
        static std::unique_ptr<bohater> bohaterInstance;
        sf::Vector2f BohaterPosition = sf::Vector2f(0.0f, 0.0f);

        game();

        void addEntity(std::unique_ptr<entities> entity);

        void updateEntities(float time);

        void moveEntities(float time);

        void spawnbohater();

        void newRoom();

        void spawnWasp();

        void run();
    }
    ;
}


