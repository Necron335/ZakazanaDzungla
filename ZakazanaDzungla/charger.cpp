#include "charger.h"
#include "game.h"
#include "bohater.h"
#include "GameGlobals.h"
#include <cstdlib> 
#include <ctime>   

bool charger::callIsDead()
{
    return isDead;
}

void charger::updateBohaterPosition(sf::Vector2f newPosition) {
    bohaterPosition = newPosition;
}

void charger::update(float time) {
    if (isAngry == false) {
        teksturabazowa.loadFromFile("textures/ChargerCalm.png");
        this->setTexture(teksturabazowa);
        speed = 100*difficulty;
        // Calculate the vector between the two points
        sf::Vector2f delta = this->getPosition() - bohaterPosition;

        // Calculate the distance using the Pythagorean theorem
        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (distance <= 500) {
            isAngry = true;
            canICharge.restart();
            speed = 10;
        }
        if (isDead == false) {
            this->setRotation(CalculateRotationAngle(this->getPosition(), bohaterPosition) + 90);
        }
    }
    else {
        teksturabazowa.loadFromFile("textures/ChargerAngry.png");
        this->setTexture(teksturabazowa);
        if (canICharge.getElapsedTime().asSeconds() >= 1) {
            speed = 500*difficulty;
            if (canICharge.getElapsedTime().asSeconds() >= 2.8) {
                isAngry = false;
                canICharge.restart();
            }
        }
        else if(isDead ==false){
            this->setRotation(CalculateRotationAngle(this->getPosition(), bohaterPosition) + 90);
        }
    }
    MyGame::bohater* bohater = MyGame::gameInstance.bohaterInstance.get();
    if (hp <= 0) {
        corpse.loadFromFile("textures/Corpse2.png");
        this->setTexture(corpse);
        speed = 0;
        isDead = true;
        isActive = false;
    }

}

void charger::takeDamage(int damage)
{
    hp -= damage;
}

void charger::move(float time) {
    if (isDead == false) {
        float angleRadians = (this->getRotation() - 90) * pi / 180.0f;

        // Calculate the movement vector based on the angle
        sf::Vector2f movement(std::cos(angleRadians), std::sin(angleRadians));

        // Scale the movement vector by the speed
        movement *= speed;

        // Update the position based on the movement vector and elapsed time
        this->setPosition(this->getPosition() + movement * time);
    }
}

charger::charger(float diff) {
    canICharge.restart();
    this->hp = this->hp * diff;
    this->speed = this->speed * diff;
    difficulty = diff;
    // Generate a random speed multiplier between 0.8 and 1.2
    float speedMultiplier = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.2f - 0.8f)));

    // Apply the multiplier to the basic speed
    speed *= speedMultiplier*diff;

    teksturabazowa.loadFromFile("textures/ChargerCalm.png");
    this->setTexture(teksturabazowa);
    // Generate a random x-coordinate at the top of the screen
// Assuming a screen width of 1920 pixels and a screen height of 1080 pixels
    int screenWidth = 1920;
    int screenHeight = 1080;

    // Randomly choose the spawn side (0: top, 1: right, 2: bottom, 3: left)
    int spawnSide = std::rand() % 4;

    float randomX, randomY;

    switch (spawnSide) {
    case 0: // Spawn on top
        randomX = static_cast<float>(std::rand() % screenWidth);
        randomY = -100.0f;
        break;
    case 1: // Spawn on the right
        randomX = screenWidth + 100.0f;
        randomY = static_cast<float>(std::rand() % screenHeight);
        break;
    case 2: // Spawn on the bottom
        randomX = static_cast<float>(std::rand() % screenWidth);
        randomY = screenHeight + 100.0f;
        break;
    case 3: // Spawn on the left
        randomX = -100.0f;
        randomY = static_cast<float>(std::rand() % screenHeight);
        break;
    default:
        // Handle unexpected case (this should never happen)
        break;
    }

    this->setPosition(randomX, randomY);
    sf::Vector2f size = static_cast<sf::Vector2f>(teksturabazowa.getSize());
    setOrigin(size.x / 2, size.y / 2);
}

