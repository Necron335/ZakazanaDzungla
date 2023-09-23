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
#include "bullet.h"
class bohater;
namespace MyGame {
    class game {
    private:
        sf::RenderWindow window;
        float pi = 3.1415;
        float bohaterspeed = 500;
        float bohaterhp = 100;
        float gamedifficulty = 1;
        int currentRoom = 1;
        float currentgamedifficulty = 1;
        int numberofenemies =0;
        int currentweapon = 1;
        float healthofhero = 20;
        float score = 0;
        sf::Clock shootTim;

    public:
        background back;
        sf::Text texthp;
        sf::Text textcroom;
        sf::Text textscore;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bohater* findBohater();
        std::vector<std::unique_ptr<entities>> vectorofentities;
        std::vector<std::unique_ptr<enemies>> vectorofenemies;
        static std::unique_ptr<bohater> bohaterInstance;
        sf::Vector2f BohaterPosition = sf::Vector2f(0.0f, 0.0f);

        game(float difficulty);

        void addEntity(std::unique_ptr<entities> entity);

        void addEnemy(std::unique_ptr<enemies> enemy);

        void initializeData(float difficulty);

        void initializeText();

        void updateStuff(float time);

        void updateEntities(float time);

        void moveEntities(float time);

        void drawText();

        //void spawnbohater();

        void newRoom();

        void spawnWasp(float gameDef);

        void run();
    }
    ;
}


