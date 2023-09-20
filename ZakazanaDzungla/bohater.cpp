#include "bohater.h"
#include "game.h" // Include the game header to access bohaterInstance
namespace MyGame {
    extern MyGame::game gameInstance;
    

    float bohater::CalculateRotationAngle() {  
            // Get the current mouse position relative to the window
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Assuming 'window' is your game's render window

            // Convert the mouse position to world coordinates
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

            // Get the position of the current 'bohater' object
            sf::Vector2f objectPosition = getPosition(); // This gets the position of the current 'bohater' object

            // Calculate the angle between the object's position and the mouse position
            float dx = worldMousePosition.x - objectPosition.x;
            float dy = worldMousePosition.y - objectPosition.y;

            // Calculate the angle in degrees
            return std::atan2(dy, dx) * 180 / static_cast<float>(pi);
    }

    void bohater::deductHP(float amount){
        // Deduct health points and handle any additional logic as needed
        hp -= amount;
        if (hp <= 0) {
            corpse.loadFromFile("textures/PanwKapeluszuCorpse.png");
            this->setTexture(corpse);
            this->speed = 0;
            this->canRotate = false;
        }
    }

    void bohater::update(float time) {
        rotationAngle = CalculateRotationAngle();
        if (canRotate == true) { setRotation(rotationAngle + 90); }
    }

    void bohater::move(float time) {
        //std::cout << this->getPosition().x << this->getPosition().y << std::endl;
        // Check if the 'W' key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            // Get the current mouse position relative to the window
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Convert the mouse position to world coordinates
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

            // Calculate the direction vector from object to mouse
            sf::Vector2f direction = worldMousePosition - getPosition();

            // Normalize the direction vector
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0) {
                direction /= length;
            }

            // Update the object's position based on the direction, speed, and elapsed time
            sf::Vector2f displacement = direction * speed * time;
            setPosition(getPosition() + displacement);

        }
    }

    bohater::bohater(sf::RenderWindow& win) : entities(), window(win) {
        teksturabazowa.loadFromFile("textures/PanwKapeluszu.png");
        this->setTexture(teksturabazowa);
        sf::Vector2f size = static_cast<sf::Vector2f>(teksturabazowa.getSize());
        setOrigin(size.x / 2, size.y / 2);
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2f objectSize = static_cast<sf::Vector2f>(teksturabazowa.getSize());

        float initialX = windowSize.x / 2.0f;
        float initialY = windowSize.y - objectSize.y / 2.0f;

        setPosition(initialX, initialY);
    }
    sf::Vector2f bohater::returnHeroPosition(bohater* bohaterakt) {
        
        if (bohaterakt == nullptr) {
            std::cout << "IM NULL POINTER" << std::endl;
        }
        if (bohaterakt) {
            sf::Vector2f position = bohaterakt->getPosition();
            //std::cout << "Bohater Position: (" << position.x << ", " << position.y << ")" << std::endl;
            return position;

        }
        /*if (gameInstance.bohaterInstance == nullptr) {
            std::cout << "IM NULL POINTER" << std::endl;
        }
        
        if (gameInstance.bohaterInstance) {
            sf::Vector2f position = gameInstance.bohaterInstance->getPosition();
            std::cout << "Bohater Position: (" << position.x << ", " << position.y << ")" << std::endl;
            return position;
            
        }*/
        //std::cout << gameInstance.bohaterInstance->getPosition().x << gameInstance.bohaterInstance->getPosition().y << std::endl;
        
        return sf::Vector2f(0.0f, 0.0f);
    }
}