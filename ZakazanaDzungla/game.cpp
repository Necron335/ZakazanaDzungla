#include "game.h"
#include"bohater.h"
namespace MyGame {
    std::unique_ptr<bohater> game::bohaterInstance = nullptr;
    game::game(float difficulty) : window(sf::VideoMode(1920, 1080), "Game") {
        bohaterInstance = std::make_unique<bohater>(window);
        addEntity(std::move(bohaterInstance));
        initializeData(difficulty);
        initializeText();
        shootTim.restart();
        
    }
    bohater* game::findBohater() {
        for (auto& entity : vectorofentities) {
            bohater* bohaterPtr = dynamic_cast<bohater*>(entity.get());
            if (bohaterPtr) {
                return bohaterPtr; // Found the bohater object, return it
            }
        }
        return nullptr; // If no bohater object is found
    }

    void game::addEntity(std::unique_ptr<entities> entity) {
        vectorofentities.push_back(std::move(entity));
    }

    void game::addEnemy(std::unique_ptr<enemies> enemy)
    {
        vectorofenemies.push_back(std::move(enemy));
    }

    void game::initializeData(float difficulty)
    {
        gamedifficulty = difficulty;
        float currentgamedifficulty = 1 * currentRoom * 0.1 * gamedifficulty * 0.2;
    }

    void game::initializeText()
    {
        sf::Font font;
        std::cout << "FontLoading in progress" << std::endl;
        if (!font.loadFromFile("fonts/Starborn.ttf")) {
            // Handle error if the font can't be loaded
            std::cout << "Could not load font" << std::endl;
        }
        std::cout << "Font loaded" << std::endl;
        texthp.setFont(font); // Set the font for the text
        texthp.setCharacterSize(60); // Set the character size (font size)
        texthp.setFillColor(sf::Color::Black); // Set the fill color
        texthp.setPosition(400,400);
        texthp.setString("Nummas");
        texthp.setString("Health Points: " + std::to_string(static_cast<int>(bohaterhp)));
        window.draw(texthp);
        
        
    }

    void game::updateStuff(float time)
    {
        float currentgamedifficulty = 10 * currentRoom*currentRoom * 0.5 * gamedifficulty * 0.5;
        std::cout << currentgamedifficulty << std::endl;
        //All bohater actions
        bohater* bohaterInstance = findBohater();
        if (bohaterInstance->hp > 0) {
            // Check if the key "1" is pressed
            // Revolver
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                bohaterInstance->changeWeapon(1);
                currentweapon = 1;
            }

            // Check if the key "2" is pressed
            // Crossbow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                bohaterInstance->changeWeapon(2);
                currentweapon = 2;
            }

            // Check if the key "3" is pressed
            // Hammer
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                bohaterInstance->changeWeapon(3);
                currentweapon = 3;
            }
            // Shooting handler regarding diffrent weapons, bolts and swings pass through enemies and deal massive damage
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (currentweapon == 1) {
                    if (shootTim.getElapsedTime().asSeconds() >= 0.2) {

                        shootTim.restart();
                        // Get the mouse click position
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                        // Calculate the direction from the bohater to the mouse click
                        sf::Vector2f bohaterPosition = bohaterInstance->returnHeroPosition(bohaterInstance);
                        sf::Vector2f direction = static_cast<sf::Vector2f>(mousePosition) - bohaterPosition;


                        // Create and add a Bullet to the game

                        std::unique_ptr<bullet> newbullet = std::make_unique<bullet>();
                        newbullet->setPosition(bohaterInstance->returnHeroPosition(bohaterInstance));
                        newbullet->setRotation(bohaterInstance->getRotation());
                        addEntity(std::move(newbullet));
                    }
                }
                if (currentweapon == 2) {
                    if (shootTim.getElapsedTime().asSeconds() >= 1) {

                        shootTim.restart();
                        // Get the mouse click position
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                        // Calculate the direction from the bohater to the mouse click
                        sf::Vector2f bohaterPosition = bohaterInstance->returnHeroPosition(bohaterInstance);
                        sf::Vector2f direction = static_cast<sf::Vector2f>(mousePosition) - bohaterPosition;


                        // Create and add a Bolt to the game

                        std::unique_ptr<bolt> newbolt = std::make_unique<bolt>();
                        newbolt->setPosition(bohaterInstance->returnHeroPosition(bohaterInstance));
                        newbolt->setRotation(bohaterInstance->getRotation());
                        addEntity(std::move(newbolt));
                    }
                }
                if (currentweapon == 3) {
                    if (shootTim.getElapsedTime().asSeconds() >= 1) {

                        shootTim.restart();
                        // Get the mouse click position
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                        // Calculate the direction from the bohater to the mouse click
                        sf::Vector2f bohaterPosition = bohaterInstance->returnHeroPosition(bohaterInstance);
                        sf::Vector2f direction = static_cast<sf::Vector2f>(mousePosition) - bohaterPosition;


                        // Create and add a Swing to the game

                        std::unique_ptr<swing> newswing = std::make_unique<swing>();
                        newswing->setPosition(bohaterInstance->returnHeroPosition(bohaterInstance));
                        newswing->setRotation(bohaterInstance->getRotation());
                        addEntity(std::move(newswing));
                    }
                }
            }
        }
    }

    

    void game::updateEntities(float time) {
        bohater* bohaterInstance = findBohater(); // Find the bohater object
        if (bohaterInstance == nullptr) {
            //handling those damn null pointers
            std::cout << "IM NULL POINTER" << std::endl;
        }
        if (bohaterInstance) {
            BohaterPosition = bohaterInstance->returnHeroPosition(bohaterInstance);
        }
        //calculating current number of alive enemies, if 0 spawn new room/wave
        numberOfEnemiesfixed = numberOfEnemies;
        for (auto& entity : vectorofentities) {
            if (entity->callIsDead() == true) {
                numberOfEnemiesfixed--;
            }
            if (entity->callIsActive() == true) {
                //handling collision with her
                entity->update(time);
                entity->calla(bohaterInstance->returnHeroPosition(bohaterInstance));
                if ((entity->isWasp()|| entity->isCharger() || entity->isShooter()) && bohaterInstance->getGlobalBounds().intersects(entity->getGlobalBounds())) {
                    if (entity->callIsDead() == false)
                    {
                        bohaterInstance->deductHP(currentgamedifficulty * time);
                    }

                }
                //handling projectiles
                if (entity->isBullet()) {
                    // Check for collision with enemies
                    for (auto& posenemy : vectorofentities) {
                        if (posenemy->isWasp()||posenemy->isCharger()||posenemy->isShooter()) {
                            if (entity->getGlobalBounds().intersects(posenemy->getGlobalBounds())) {
                                if (posenemy->callIsDead() == false) {
                                    posenemy->takeDamage(5);
                                    entity->handleCollisionWithEnemy();
                                }
                            }
                        }
                    }
                }
                if (entity->isBolt()) {
                    // Check for collision with enemies
                    for (auto& posenemy : vectorofentities) {
                        if (posenemy->isWasp() || posenemy->isCharger() || posenemy->isShooter()) {
                            if (entity->getGlobalBounds().intersects(posenemy->getGlobalBounds())) {
                                if (posenemy->callIsDead() == false) {
                                    posenemy->takeDamage(3);
                                    entity->handleCollisionWithEnemy();
                                }
                            }
                        }
                    }
                }
                if (entity->isSwing()) {
                    // Check for collision with enemies
                    for (auto& posenemy : vectorofentities) {
                        if (posenemy->isWasp() || posenemy->isCharger() || posenemy->isShooter()) {
                            if (entity->getGlobalBounds().intersects(posenemy->getGlobalBounds())) {
                                if (posenemy->callIsDead() == false) {
                                    posenemy->takeDamage(10);
                                    entity->handleCollisionWithEnemy();
                                }
                            }
                        }
                    }
                }
            }
        }
        if (numberOfEnemiesfixed <= 0) {
            newRoom();

        }
        //delivering bohaterposition to everyone
        for (auto& entity : vectorofentities) {
            wasp* waspInstance = dynamic_cast<wasp*>(entity.get());
            if (waspInstance) {
                waspInstance->updateBohaterPosition(BohaterPosition);
            }
            
        }
        for (auto& entity : vectorofentities) {
            charger* chargerInstance = dynamic_cast<charger*>(entity.get());
            if (chargerInstance) {
                chargerInstance->updateBohaterPosition(BohaterPosition);
            }

        }
        for (auto& entity : vectorofentities) {
            shooter* shooterInstance = dynamic_cast<shooter*>(entity.get());
            if (shooterInstance) {
                shooterInstance->updateBohaterPosition(BohaterPosition);
            }

        }
    }


    void game::moveEntities(float time) {
        for (auto& entity : vectorofentities) {
            entity->move(time);
        }
    }

    void game::drawText()
    {
        //window.draw(texthp);
        sf::Font font;
        if (!font.loadFromFile("fonts/Starborn.ttf")) {
            // Handle error if the font can't be loaded
            std::cout << "Could not load font" << std::endl;
        }
        // I can just put all texts to array and execute all of this in a loop but who needs that right now?
        texthp.setFont(font); // Set the font for the text
        texthp.setCharacterSize(60); // Set the character size (font size)
        texthp.setFillColor(sf::Color::Black); // Set the fill color
        texthp.setPosition(0, 0);
        textcroom.setFont(font); // Set the font for the text
        textcroom.setCharacterSize(20); // Set the character size (font size)
        textcroom.setFillColor(sf::Color::Black); // Set the fill color
        textcroom.setPosition(0, 100);
        textscore.setFont(font); // Set the font for the text
        textscore.setCharacterSize(20); // Set the character size (font size)
        textscore.setFillColor(sf::Color::Black); // Set the fill color
        textscore.setPosition(0, 140);
        bohater* bohaterInstance = findBohater();
        if (bohaterInstance->isDead == false) {
            texthp.setString("Health Points: " + std::to_string(static_cast<int>(bohaterInstance->hp)));
        }
        else {
            texthp.setString("Health Points: 0");
        }
        textcroom.setString("Current room: "+std::to_string(currentRoom-1));
        textscore.setString("Enemies: "+std::to_string(numberOfEnemiesfixed));
        window.draw(texthp);
        window.draw(textcroom);
        window.draw(textscore);
    }
    //Remnant
    /*void game::spawnbohater() {
        bohaterInstance = std::make_unique<bohater>(window);
        addEntity(std::move(bohaterInstance));
    }*/

    void game::newRoom() {
        currentRoom++;
        int numEnemies = std::rand() % static_cast<int>(20 * currentgamedifficulty) + 4;
        for (int i = 0; i < numEnemies; ++i) {
            numberOfEnemies++;
            // Create and add the enemy to the game
            int randomnum = std::rand() % 3 + 1;
            switch (randomnum)
            {case(1):
                spawnWasp(currentgamedifficulty);
                break;
            case(2):
                spawnShooter(currentgamedifficulty);
                break;
            case(3):
                spawnCharger(currentgamedifficulty); 
                break;
            //case(4): spawn corpse??? not enough time i guess
            default:
                break;
            }
        }
    }
    //Spawners
    void game::spawnWasp(float gameDef) {
        std::unique_ptr<wasp> newWasp = std::make_unique<wasp>(currentgamedifficulty);
        addEntity(std::move(newWasp));
    }

    void game::spawnCharger(float gameDef)
    {
        std::unique_ptr<charger> newCharger = std::make_unique<charger>(currentgamedifficulty);
        addEntity(std::move(newCharger));
    }

    void game::spawnShooter(float gameDef)
    {
        std::unique_ptr<shooter> newShooter = std::make_unique<shooter>(currentgamedifficulty);
        addEntity(std::move(newShooter));
    }

    void game::spawnProjectile(sf::Vector2f startPosition, float direction)
    {
        std::unique_ptr<stinger> newStinger = std::make_unique<stinger>(startPosition, direction);
        addEntity(std::move(newStinger));
    }

    void game::run() {
        background back;
        newRoom();
        std::cout << currentgamedifficulty;
        sf::Clock clock;
        // Game loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Measure the time elapsed since the last loop iteration
            float elapsedTime = clock.restart().asSeconds();

            // Update entities with the elapsed time
            updateStuff(elapsedTime);
            updateEntities(elapsedTime);
            moveEntities(elapsedTime);

            window.clear();
            window.draw(back);
            // Draw entities and other game elements
            for (auto& entity : vectorofentities) {
                window.draw(static_cast<sf::Drawable&>(*entity));
            }
            drawText();

            

            window.display();
        }
    }
}