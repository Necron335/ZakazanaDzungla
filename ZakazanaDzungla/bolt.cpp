#include "bolt.h"

void bolt::move(float time)
{
    // Implement your move logic here
    float angleRadians = (this->getRotation() - 90) * pi / 180.0f;

    // Calculate the movement vector based on the angle
    sf::Vector2f movement(std::cos(angleRadians), std::sin(angleRadians));

    // Scale the movement vector by the speed
    movement *= speed;
    // Update the position based on the movement vector and elapsed time
    this->setPosition(this->getPosition() + movement * time);
}

void bolt::update(float time)
{
    if (alivetime.getElapsedTime().asSeconds() >= timetodie) {
        handleCollisionWithEnemy();
    }
}

bolt::bolt() {

    teksturabazowa.loadFromFile("textures/bolt.png");
    this->setTexture(teksturabazowa);
    this->speed = 1000;
    alivetime.restart();

}

void bolt::handleCollisionWithEnemy()
{// Deal damage to the enemy and destroy the bullet
    if (alivetime.getElapsedTime().asSeconds() <= timetodie) {
        
    }
    else {
        this->speed = 0;
        this->setPosition(10000, 10000);
        this->isActive = false;
    }
    
}
