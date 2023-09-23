#include "charger.h"
#include "game.h" // Include the game header to access game::BohaterPosition
#include "bohater.h"
#include "GameGlobals.h"
#include <cstdlib> // Include this for random number generation
#include <ctime>   // Include this for seeding the random number generator

bool charger::callIsDead()
{
    return isDead;
}

void charger::updateBohaterPosition(sf::Vector2f newPosition) {
    bohaterPosition = newPosition;
    //wstd::cout << bohaterPosition.x << bohaterPosition.y;
}

void charger::update(float time) {
    if (isAngry == false) {
        teksturabazowa.loadFromFile("textures/ChargerCalm.png");
        this->setTexture(teksturabazowa);
        speed = 100;
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
            speed = 500;
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
        // Implement your move logic here
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
    this->speed = this->speed * diff * 0.5;
    // Generate a random speed multiplier between 0.8 and 1.2
    float speedMultiplier = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.2f - 0.8f)));

    // Apply the multiplier to the basic speed
    speed *= speedMultiplier;
    //if (!teksturabazowa.loadFromFile("textures/wasp.png")) {
    //    // Handle error loading texture
    //}
    //frames.push_back(teksturabazowa);
    //if (!teksturabazowa.loadFromFile("textures/wasp2.png")) {
    //    // Handle error loading texture
    //}
    //frames.push_back(teksturabazowa);
    //for (int i = 1; i <= 2; i++) {
    //    sf::Texture frame;
    //    
    //    
    //}
    teksturabazowa.loadFromFile("textures/ChargerCalm.png");
    this->setTexture(teksturabazowa);
    // Generate a random x-coordinate at the top of the screen
    float randomX = static_cast<float>(std::rand() % 1920); // Assuming a screen width of 1920 pixels

    // Set the initial position with the random x-coordinate and a fixed y-coordinate (at the top)
    this->setPosition(randomX, 100); // 0 is the top of the screen
    sf::Vector2f size = static_cast<sf::Vector2f>(teksturabazowa.getSize());
    setOrigin(size.x / 2, size.y / 2);
}

