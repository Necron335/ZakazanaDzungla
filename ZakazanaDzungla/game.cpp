#include "game.h"
#include"bohater.h"
namespace MyGame {
    std::unique_ptr<bohater> game::bohaterInstance = nullptr;
    game::game() : window(sf::VideoMode(1920, 1080), "Game") {
        bohaterInstance = std::make_unique<bohater>(window);
        addEntity(std::move(bohaterInstance));
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
            if (entity->isWasp() && bohaterInstance->getGlobalBounds().intersects(entity->getGlobalBounds())) {
                bohaterInstance->deductHP(1*time);
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

    /*void game::spawnbohater() {
        bohaterInstance = std::make_unique<bohater>(window);
        addEntity(std::move(bohaterInstance));
    }*/

    void game::newRoom() {
        // Implementation for new room
    }

    void game::spawnWasp() {
        std::unique_ptr<wasp> newWasp = std::make_unique<wasp>();
        addEntity(std::move(newWasp));
    }

    void game::run() {
        background back;
        spawnWasp();
        spawnWasp();
        spawnWasp();
        spawnWasp();
        spawnWasp();

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
            updateEntities(elapsedTime);
            moveEntities(elapsedTime);

            window.clear();
            window.draw(back);
            // Draw entities and other game elements
            for (auto& entity : vectorofentities) {
                window.draw(static_cast<sf::Drawable&>(*entity));
            }

            window.display();
        }
    }
}