#include "swing.h"
void swing::move(float time)
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

void swing::update(float time)
{
    if (alivetime.getElapsedTime().asSeconds() >= timetodie) {
        handleCollisionWithEnemy();
    }
}

swing::swing() {
    timetodie = 0.15;
    teksturabazowa.loadFromFile("textures/swing.png");
    this->setTexture(teksturabazowa);
    this->speed = 1500;
    alivetime.restart();

}

void swing::handleCollisionWithEnemy()
{// Deal damage to the enemy and destroy the bullet
    if (alivetime.getElapsedTime().asSeconds() <= timetodie) {

    }
    else {
        this->speed = 0;
        this->setPosition(10000, 10000);
        this->isActive = false;
    }

}
