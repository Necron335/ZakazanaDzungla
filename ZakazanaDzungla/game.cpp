#include "game.h"
#include"bohater.h"
namespace MyGame {
    std::unique_ptr<bohater> game::bohaterInstance = nullptr;
    game::game(float difficulty) : window(sf::VideoMode(1920, 1080), "Game") {
        bohaterInstance = std::make_unique<bohater>(window);
        addEntity(std::move(bohaterInstance));
        initializeData(difficulty);
        initializeText();
        
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
        bohater* bohaterInstance = findBohater();
        // Check if the key "1" is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            bohaterInstance->changeWeapon(1);
            currentweapon = 1;
        }

        // Check if the key "2" is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            bohaterInstance->changeWeapon(2);
            currentweapon = 2;
        }

        // Check if the key "3" is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            bohaterInstance->changeWeapon(3);
            currentweapon = 3;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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

    

    void game::updateEntities(float time) {
        bohater* bohaterInstance = findBohater(); // Find the bohater object
        if (bohaterInstance == nullptr) {
            std::cout << "IM NULL POINTER" << std::endl;
        }
        if (bohaterInstance) {
            BohaterPosition = bohaterInstance->returnHeroPosition(bohaterInstance);
            //std::cout << "Jestem Bohater" << BohaterPosition.x << BohaterPosition.y << std::endl;
        }
        
        //std::cout << BohaterPosition.x << BohaterPosition.y << std::endl;
        
        for (auto& entity : vectorofentities) {
            entity->update(time);
            entity->calla(bohaterInstance->returnHeroPosition(bohaterInstance));
            if (entity->isWasp() && bohaterInstance->getGlobalBounds().intersects(entity->getGlobalBounds())) {
                bohaterInstance->deductHP(currentgamedifficulty*time);
            }
            if (entity->isBullet()) {
                // Check for collision with enemies
                for (auto& enem : vectorofenemies) {
                    if (enem == nullptr) {
                        //std::cout << "Im null pointer" << std::endl;
                    }
                    if (enem && entity) { // Check if enem and entity are not nullptr
                        if (entity->getGlobalBounds().intersects(enem->getGlobalBounds())) {
                            // Handle collision with the enemy
                            enem->takeDamage(1);
                            std::cout << "Collision detected with wasp enemy!" << std::endl;
                            std::cout << "Bullet Position: (" << entity->getPosition().x << ", " << entity->getPosition().y << ")" << std::endl;
                            std::cout << "Wasp Position: (" << enem->getPosition().x << ", " << enem->getPosition().y << ")" << std::endl;
                        }
                    }
                }
            }
        }
        for (auto& entity : vectorofentities) {
            wasp* waspInstance = dynamic_cast<wasp*>(entity.get());
            if (waspInstance) {
                //std::cout << "Jestem Wasp"<<BohaterPosition.x<<BohaterPosition.y << std::endl;
                waspInstance->updateBohaterPosition(BohaterPosition);
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
        textscore.setString("Current score: " + std::to_string(score));
        textscore.setString("Current score: "+std::to_string(static_cast<int>(score)));
        window.draw(texthp);
        window.draw(textcroom);
        window.draw(textscore);
    }

    /*void game::spawnbohater() {
        bohaterInstance = std::make_unique<bohater>(window);
        addEntity(std::move(bohaterInstance));
    }*/

    void game::newRoom() {
        // Implementation for new room
        //std::cout << "newRoom";
        currentRoom++;
        int numEnemies = std::rand() % static_cast<int>(10 * currentgamedifficulty) + 1;
        //std::cout << numEnemies;
        for (int i = 0; i < numEnemies; ++i) {
            numberofenemies++;
            // Create and add the enemy to the game
            int randomnum = std::rand() % 3 + 1;
            //std::cout << randomnum;
            switch (randomnum)
            {case(1):
                spawnWasp(currentgamedifficulty);
                numberofenemies++;
            case(2):
                //spawn shooter
            case(3):
                //spawn charger
            //case(4): spawn corpse???
            default:
                break;
            }
        }
    }

    void game::spawnWasp(float gameDef) {
        std::unique_ptr<wasp> newWasp = std::make_unique<wasp>(currentgamedifficulty);
        addEntity(std::move(newWasp));
        addEnemy(std::move(newWasp));
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