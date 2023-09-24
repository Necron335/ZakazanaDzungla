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
#include "charger.h"
#include "background.h"
#include "bullet.h"
#include "shooter.h"
#include "bolt.h"
#include "swing.h"
#include "stinger.h"
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

        int currentweapon = 0;
        float healthofhero = 20;
        float score = 0;
        sf::Clock shootTim;

    public:
        background back;
        sf::Text texthp;
        sf::Text textcroom;
        sf::Text textscore;
        int numberOfEnemies = 0;
        int numberOfEnemiesfixed = 0;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bohater* findBohater();
        std::vector<std::unique_ptr<entities>> vectorofentities;
        std::vector<std::unique_ptr<enemies>> vectorofenemies;
        static std::unique_ptr<bohater> bohaterInstance;
        sf::Vector2f BohaterPosition = sf::Vector2f(0.0f, 0.0f);

        game(float difficulty);
        //Pack everything to one vector
        void addEntity(std::unique_ptr<entities> entity);
        //I wanted to also pack all enemies to second vector but due to nullptr issues i worked around it with bools
        void addEnemy(std::unique_ptr<enemies> enemy);
        //Self explainatory
        void initializeData(float difficulty);
        //Same here
        void initializeText();
        //Extension of update function, i didnt want to spread it too far
        void updateStuff(float time);
        // update every entity
        void updateEntities(float time);
        // move every entity
        void moveEntities(float time);
        // draw text
        void drawText();
        //worked around it, no need for multiple heroes, and also i dont want to have nullptr before its creation
        //void spawnbohater();
        //New room of enemies, new wave
        void newRoom();
        //spawning handler
        void spawnWasp(float gameDef);

        void spawnCharger(float gameDef);

        void spawnShooter(float gameDef);

        void spawnProjectile(sf::Vector2f startPosition, float direction);
        //game loop
        void run();
    }
    ;
}


