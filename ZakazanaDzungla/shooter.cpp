#include "shooter.h"
#include "game.h" 
#include "bohater.h"
#include "GameGlobals.h"
#include <cstdlib> 
#include <ctime>   
#include <random>
bool shooter::callIsDead()
{
    return isDead;
}

void shooter::updateBohaterPosition(sf::Vector2f newPosition) {
    bohaterPosition = newPosition;
}

void shooter::update(float time) {
    if (isDead == false) {
        this->setRotation(CalculateRotationAngle(this->getPosition(), bohaterPosition) + 90);
    }
    MyGame::bohater* bohater = MyGame::gameInstance.bohaterInstance.get();
    if (hp <= 0) {
        corpse.loadFromFile("textures/Corpse3.png");
        this->setTexture(corpse);
        speed = 0;
        isDead = true;
        isActive = false;
    }
    
    if (canShoot.getElapsedTime().asSeconds() >= timedelay) {
        //shootin();
        //If i could i would shoot :/
        canShoot.restart();
    }
}

void shooter::takeDamage(int damage)
{
    hp -= damage;
}

void shooter::move(float time) {
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

void shooter::shootin()
{
    MyGame::gameInstance.spawnProjectile(this->getPosition(), this->getRotation());
}

shooter::shooter(float diff) {
    canShoot.restart();
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution for the random number
    std::uniform_int_distribution<int> distribution(1, 100);

    // Generate a random number between 1 and 100
    int randomNumber = distribution(gen);

    // Divide the random number by 100 to get a floating-point value between 0.01 and 1.00
    float result = static_cast<float>(randomNumber) / 100.0f;
    timedelay += result;
    this->hp = this->hp * diff;
    this->speed = this->speed * diff * 0.5;
    // Generate a random speed multiplier between 0.8 and 1.2
    float speedMultiplier = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.2f - 0.8f)));

    // Apply the multiplier to the basic speed
    speed *= speedMultiplier;
    
    teksturabazowa.loadFromFile("textures/Shooter.png");
    this->setTexture(teksturabazowa);
    // Generate a random x-coordinate at the top of the screen
    float randomX = static_cast<float>(std::rand() % 1920); // Assuming a screen width of 1920 pixels
    float randomY = static_cast<float>(std::rand() % 1080);
    // Set the initial position with the random x-coordinate and a fixed y-coordinate (at the top)
    this->setPosition(randomX, randomY);
    sf::Vector2f size = static_cast<sf::Vector2f>(teksturabazowa.getSize());
    setOrigin(size.x / 2, size.y / 2);
}