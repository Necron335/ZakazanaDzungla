#include "stinger.h"

void stinger::move(float time)
{
    //Rotation Schenenigans
    float angleRadians = (this->getRotation() - 90) * pi / 180.0f;

    // Calculate the movement vector based on the angle
    sf::Vector2f movement(std::cos(angleRadians), std::sin(angleRadians));

    // Scale the movement vector by the speed
    movement *= speed;
    // Update the position based on the movement vector and elapsed time
    this->setPosition(this->getPosition() + movement * time);
}

void stinger::update(float time)
{
    //remnant after bullet, it was supposed to work just the same, but conditions in game would be different but alas its not working
    if (alivetime.getElapsedTime().asSeconds() >= timetodie) {
        handleCollisionWithEnemy();
    }
}

stinger::stinger(sf::Vector2f startpos, float direction) {

    teksturabazowa.loadFromFile("textures/Stinger.png");
    this->setTexture(teksturabazowa);
    this->speed = 1000;
    this->setPosition(startpos);
    this->setRotation(direction);

}

void stinger::handleCollisionWithEnemy()
{// Deal damage to the hero and destroy the stinger, make it disabled~
    this->speed = 0;
    this->setPosition(10000, 10000);
    this->isActive = false;
}
