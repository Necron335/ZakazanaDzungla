#include "bullet.h"

void bullet::move(float time)
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

void bullet::update(float time)
{

}

bullet::bullet(){

    teksturabazowa.loadFromFile("textures/Bullet.png");
    this->setTexture(teksturabazowa);
    this->speed = 1000;
    
}

void bullet::handleCollisionWithEnemy()
{// Deal damage to the enemy and destroy the bullet
    this->speed = 0;
    this->setPosition(10000,10000);
    this->isActive = false;
}
